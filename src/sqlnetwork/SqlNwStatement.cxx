/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <SqlNwStatement.h>
#include <Network.h>

DbRetVal SqlNwStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    isSel = false;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    if (isPrepared) free(); 
    if (nullInfoSel) { ::free(nullInfoSel);  nullInfoSel = NULL; }  
    if (nullInfoDml) { ::free(nullInfoDml);  nullInfoDml = NULL; }  
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->stmtString = stmtstr;
    pkt->stmtLength = os::align(strlen(stmtstr) + 1);
    pkt->marshall(); 
    rv = conn->send(SQL_NW_PKT_PREPARE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    int response = 0;
    rv = conn->receive();
    if (rv != OK) { 
        printError(rv, "Unable to Receive from peer");
        return rv;
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr == 0) { delete pkt; return ErrPeerResponse; }
    if (rpkt->isSelect) isSel = true; else isSel = false;
    int params = *(ptr + 2);
    int proj = *(ptr + 3);
    stmtID = rpkt->stmtID;
    char *buffer = NULL;
    if (params) {
        PacketHeader header;
        int fd = ((TCPClient *)(conn->nwClient))->sockfd;
        int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
//        printf("HEADER says packet type is %d\n", header.packetType);
        buffer = (char*) malloc(header.packetLength);
        numbytes = os::recv(fd,buffer,header.packetLength,0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        SqlPacketParamMetadata *mdpkt = new SqlPacketParamMetadata();
        mdpkt->setBuffer(buffer);
        mdpkt->unmarshall();
        noOfParams = mdpkt->noParams;
        //allocate null info for dml paramterized stmts to be filled up 
        //during set null
        int nullInfoLen = os::align(noOfParams);
        nullInfoDml = (char *) malloc(nullInfoLen);
        memset(nullInfoDml, 0, nullInfoLen);

        BindSqlField *bindField=NULL;
        FieldInfo *fldInfo = new FieldInfo();
        char *ptr = (char *) mdpkt->data;
        for (int i=0; i < noOfParams; i++) {
            *fldInfo = *(FieldInfo *) ptr;
            bindField = new BindSqlField();
            strcpy(bindField->fName, fldInfo->fldName);
            bindField->type = fldInfo->type;
            bindField->length = fldInfo->length;
            bindField->offset = fldInfo->offset;
            strcpy(bindField->defaultValueBuf, fldInfo->defaultValueBuf);
            bindField->isNull = fldInfo->isNull;
            bindField->isPrimary = fldInfo->isPrimary;
            bindField->isDefault = fldInfo->isDefault;
            bindField->isUnique = fldInfo->isUnique;
            if (bindField->type == typeBinary)
                bindField->value = AllDataType::alloc(bindField->type, 2 * bindField->length);
            else bindField->value = AllDataType::alloc(bindField->type, bindField->length);
            paramList.append(bindField);
            ptr += sizeof (FieldInfo);
        }
        delete mdpkt;
    }
    if (proj) {
        PacketHeader header;
        int fd = ((TCPClient *)(conn->nwClient))->sockfd;
        int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
//        printf("HEADER says packet type is %d\n", header.packetType);
        buffer = (char*) malloc(header.packetLength);
        numbytes = os::recv(fd,buffer,header.packetLength,0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        SqlPacketProjMetadata *prjmdpkt = new SqlPacketProjMetadata();
        prjmdpkt->setBuffer(buffer);
        prjmdpkt->unmarshall();
        noOfProjs = prjmdpkt->noProjs;
        BindSqlProjectField *prjFld=NULL;
        FieldInfo *fldInfo = new FieldInfo();
        char *ptr = (char *) prjmdpkt->data;
        for (int i=0; i < noOfProjs; i++) {
            *fldInfo = *(FieldInfo *) ptr;
            prjFld = new BindSqlProjectField();
            strcpy(prjFld->fName, fldInfo->fldName);
            prjFld->type = fldInfo->type;
            prjFld->length = fldInfo->length;
            prjFld->offset = fldInfo->offset;
            strcpy(prjFld->defaultValueBuf, fldInfo->defaultValueBuf);
            prjFld->isNull = fldInfo->isNull;
            prjFld->isPrimary = fldInfo->isPrimary;
            prjFld->isDefault = fldInfo->isDefault;
            prjFld->isUnique = fldInfo->isUnique;
            if (prjFld->type == typeBinary)
                prjFld->value = AllDataType::alloc(prjFld->type, 2 * prjFld->length);
            else prjFld->value = AllDataType::alloc(prjFld->type, prjFld->length);
            bindList.append(prjFld);
            ptr += sizeof (FieldInfo);
        }
        delete prjmdpkt;
    }
    isPrepared = true;
    delete pkt;
    return rv;
}

DbRetVal SqlNwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    if (!isPrepared) return ErrNotPrepared;
    SqlPacketExecute *pkt = new SqlPacketExecute();
    pkt->stmtID = getStmtID();
    pkt->noParams=paramList.size();
    pkt->setParams(paramList);
    pkt->setNullInfo(nullInfoDml);
    pkt->marshall();
    rv = conn->send(SQL_NW_PKT_EXECUTE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    rv = conn->receive();
    if (rv != OK) return rv; 
    memset(nullInfoDml, 0, os::align(pkt->noParams));
    //if(pkt->noParams) delete [] pkt->paramValues;
    delete pkt;
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    rowsAffected = rpkt->rows;
    if (*ptr != 1) {
        printError(rpkt->errRetVal, "%s", rpkt->errorString);
        return rpkt->errRetVal;
    }
    return rv;
}

DbRetVal SqlNwStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated. Use setParamXXX instead\n");
    return rv;
}

DbRetVal SqlNwStatement::bindField(int pos, void* value)
{
    if (!isPrepared) return OK;
    BindSqlProjectField *prjFld = (BindSqlProjectField *) bindList.get(pos);
    prjFld->value = value;
    return OK;
}
void* SqlNwStatement::fetch()
{
    DbRetVal rv = OK;
    return fetch(rv);
}

void* SqlNwStatement::fetch(DbRetVal &ret)
{
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        ret = ErrNoConnection;
        return NULL;
    }
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;

    DbRetVal rv = conn->nwClient->send(SQL_NW_PKT_FETCH, getStmtID());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return NULL;
    }
    
    /*SqlPacketFetch *pkt = new SqlPacketFetch();
    pkt->stmtID = getStmtID();
    pkt->marshall();
    DbRetVal rv = conn->send(SQL_NW_PKT_FETCH, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return NULL;
    }*/
//    printf("HEADER says packet type is %d\n", header.packetType);
    int rowLength=0;
    int dummy =0;
    int fd = ((TCPClient *)(conn->nwClient))->sockfd;
    int numbytes = os::recv(fd, &rowLength, 4, 0);
    if (rowLength ==1 ) return NULL;
    else if (rowLength == 2) {ret = ErrUnknown; return NULL; }

    if ((numbytes = os::send(fd, &dummy, 4,MSG_NOSIGNAL)) == -1) {
        if (errno == EPIPE) {
            printError(ErrNoConnection, "connection not present");
            return NULL;
        }
        printError(ErrOS, "Unable to send the packet\n");
        return NULL;
    }
    char *rowBuffer = (char*) malloc(rowLength);
    numbytes = os::recv(fd,rowBuffer,rowLength,0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        return NULL;
    }
    SqlPacketResultSet *rspkt = new SqlPacketResultSet();
    rspkt->setBuffer(rowBuffer);
    rspkt->setProjList(bindList);
    rspkt->noProjs = bindList.size();
    if (nullInfoSel == NULL) 
        nullInfoSel = (char *) malloc(os::align(rspkt->noProjs));
    memset(nullInfoSel, 0, os::align(rspkt->noProjs));
    rspkt->setNullInfo(nullInfoSel);
    rspkt->unmarshall();
    delete [] rspkt->projValues;
    ptrToFirstField = bindList.get(1);
    delete rspkt;
    //delete pkt;
    return ptrToFirstField;
}


void* SqlNwStatement::fetchAndPrint(bool SQL)
{
    if (!isPrepared) return NULL;
    void *tuple = NULL;
    BindSqlProjectField *fld = NULL;
    tuple = fetch();
    if (NULL == tuple) return NULL;
    for(int i = 0; i < noOfProjs; i++) {
        fld = (BindSqlProjectField *) bindList.get(i + 1);
        if (isFldNull(i+1)) printf("NULL");
        else AllDataType::printVal(fld->value, fld->type, fld->length);
        printf("\t");
    }
    return tuple;
}

void* SqlNwStatement::next()
{
    return fetch();
}

DbRetVal SqlNwStatement::close()
{
    if (!isPrepared) return OK;
    //TODO
    return OK;
}

void* SqlNwStatement::getFieldValuePtr( int pos )
{
    BindSqlProjectField *fld=(BindSqlProjectField *) bindList.get(pos+1);
    return fld->value;   
}

int SqlNwStatement::noOfProjFields()
{
    if (!isPrepared) return 0;
    return noOfProjs;
}

int SqlNwStatement::noOfParamFields()
{
    if (!isPrepared) return 0;
    return noOfParams;
}

DbRetVal SqlNwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    BindSqlProjectField *prjFld = (BindSqlProjectField *) bindList.get(projpos);
    strcpy(fInfo->fldName, prjFld->fName);
    fInfo->type = prjFld->type;
    fInfo->length = prjFld->length;
    fInfo->offset = prjFld->offset;
    strcpy(fInfo->defaultValueBuf, prjFld->defaultValueBuf);
    fInfo->isNull = prjFld->isNull;
    fInfo->isPrimary = prjFld->isPrimary;
    fInfo->isDefault = prjFld->isDefault;
    fInfo->isUnique = prjFld->isUnique;
    return OK;
}

DbRetVal SqlNwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    BindSqlField *bindField = (BindSqlField *) paramList.get(parampos);
    strcpy(fInfo->fldName, bindField->fName);
    fInfo->type = bindField->type;
    fInfo->length = bindField->length;
    fInfo->offset = bindField->offset;
    strcpy(fInfo->defaultValueBuf, bindField->defaultValueBuf);
    fInfo->isNull = bindField->isNull;
    fInfo->isPrimary = bindField->isPrimary;
    fInfo->isDefault = bindField->isDefault;
    fInfo->isUnique = bindField->isUnique;
    return OK;
}

DbRetVal SqlNwStatement::free()
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    if (!isPrepared) return OK;
    SqlPacketFree *pkt = new SqlPacketFree();
    pkt->stmtID = getStmtID();
    pkt->marshall();
    rv = conn->send(SQL_NW_PKT_FREE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    rv = conn->receive();
    if (rv != OK) return rv;
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr != 1) {
        printf("there is some error\n");
        return ErrPeerResponse;
    }
    ListIterator itprm = paramList.getIterator();
    BindSqlField *fld = NULL;
    while((fld = (BindSqlField *) itprm.nextElement()) != NULL) {
        if (fld->value) ::free(fld->value); delete fld;
    }
    paramList.reset();
    ListIterator itprj = bindList.getIterator();
    BindSqlProjectField *pfld = NULL;
    while((pfld = (BindSqlProjectField *) itprj.nextElement()) != NULL) {
        delete pfld;
    }
    if (nullInfoSel) { ::free(nullInfoSel); nullInfoSel = NULL; }
    if (nullInfoDml) { ::free(nullInfoDml); nullInfoDml = NULL; }
    bindList.reset();

    isPrepared = false;
    delete pkt;
    return rv;
}

// In all the following setXXXParam functions type and length fields are 
// reinitialized to accommodate fix for MySQL bug #1382 
// SQLDescribeParam returns the same type information

void SqlNwStatement::setShortParam(int paramPos, short value)
{
    if (!isPrepared) return;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeShort;
    bindField->length = AllDataType::size(typeShort);
    *(short *) bindField->value = value;
    return;
}

void SqlNwStatement::setIntParam(int paramPos, int value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeInt;
    bindField->length = sizeof(int);
    *(int *) bindField->value = value;
    return;
}

void SqlNwStatement::setLongParam(int paramPos, long value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeLong;
    bindField->length = sizeof(long);
    *(long *) bindField->value = value;
    return;

}

void SqlNwStatement::setLongLongParam(int paramPos, long long value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeLongLong;
    bindField->length = AllDataType::size(typeLongLong);
    *(long long *) bindField->value = value;
    return;
}

void SqlNwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeByteInt;
    bindField->length = AllDataType::size(typeByteInt);
    *(ByteInt *) bindField->value = value;
    return;
}

void SqlNwStatement::setFloatParam(int paramPos, float value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeFloat;
    bindField->length = AllDataType::size(typeFloat);
    *(float *) bindField->value = value;
    return;
}

void SqlNwStatement::setDoubleParam(int paramPos, double value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeDouble;
    bindField->length = AllDataType::size(typeDouble);
    *(double *) bindField->value = value;
    return;
}

void SqlNwStatement::setStringParam(int paramPos, char *value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeString;
    strcpy((char *) bindField->value, value);
    return;
}

void SqlNwStatement::setDateParam(int paramPos, Date value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeDate;
    bindField->length = sizeof(Date);
    *(Date *)bindField->value = value;
    return;
}

void SqlNwStatement::setTimeParam(int paramPos, Time value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeTime;
    bindField->length = sizeof(Time);
    * (Time *) bindField->value = value;
    return;
}

void SqlNwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeTimeStamp;
    bindField->length = sizeof(TimeStamp);
    *(TimeStamp *) bindField->value = value;
    return;
}

void SqlNwStatement::setBinaryParam(int paramPos, void *value, int length)
{
    if (!isPrepared) return;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    bindField->type = typeBinary;
    memcpy(bindField->value, value, 2 * bindField->length);
    return;
}

void SqlNwStatement::getPrimaryKeyFieldName(char *tablename, char *pkfieldname)
{
    if (pkfieldname == NULL) return;
    //TODO
    return;
}

List SqlNwStatement::getAllTableNames(DbRetVal &ret)
{
    DbRetVal rv = OK;
    
    ListIterator tblIter = tblNameList.getIterator();
    while (tblIter.hasElement()) delete tblIter.nextElement();
    tblNameList.reset();

    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        ret = ErrNoConnection;
    }
    rv = conn->send(SQL_NW_PKT_SHOWTABLES);
    rv = conn->receive();
    if (rv != OK) {
        printError(rv, "Unable to Receive from peer");
        ret = rv;
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr == 0) { ret = ErrPeerResponse; }
    stmtID = rpkt->stmtID;
    int noOfTables = rpkt->rows;
    PacketHeader header;
    int fd = ((TCPClient *)(conn->nwClient))->sockfd;
    int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        ret = ErrOS;
    }
//    printf("HEADER says packet type is %d\n", header.packetType);
    char *buffer = (char*) malloc(header.packetLength);
    numbytes = os::recv(fd,buffer,header.packetLength,0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        ret = ErrOS;
    }
    SqlPacketShowTables *pkt = new SqlPacketShowTables();
    pkt->setBuffer(buffer);
    rv = pkt->unmarshall();
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        ret = rv;
    }
    ptr = (char *)pkt->data;
    while (noOfTables) {
        Identifier *id = new Identifier();
        strncpy(id->name, ptr, IDENTIFIER_LENGTH);
        ptr += IDENTIFIER_LENGTH;
        noOfTables--;
        tblNameList.append(id);
    }
    return tblNameList;
}

bool SqlNwStatement::isFldNull(int pos)
{
    if (nullInfoSel[pos - 1]) return true;
    else return false;
}

bool SqlNwStatement::isFldNull(char *fname) 
{
    for (int i=0; i < bindList.size(); i++) {
        BindSqlProjectField *fld = (BindSqlProjectField *) bindList.get(i+1);
        if (strcmp(fname, fld->fName) == 0) return isFldNull(i+1);
    }
}

void SqlNwStatement::setNull(int fldPos)
{
    if (nullInfoDml) nullInfoDml[fldPos-1] = 1;
}
