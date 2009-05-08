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
#include <os.h>
#include <SqlNetworkHandler.h>
#include <AbsSqlConnection.h>
#include <SqlConnection.h>
#include <SqlOdbcConnection.h>
#include <AbsSqlStatement.h>
#include <SqlStatement.h>
#include <SqlOdbcStatement.h>
#include <SqlLogStatement.h>
#include <Parser.h>

List SqlNetworkHandler::stmtList;
List SqlNetworkHandler::tableNameList;
AbsSqlConnection* SqlNetworkHandler::conn;
SqlApiImplType SqlNetworkHandler::type;
int SqlNetworkHandler::stmtID;
int SqlNetworkHandler::sockfd;

void *SqlNetworkHandler::process(PacketHeader &header, char *buffer)
{
    DbRetVal rv = OK;
    char *ptr = NULL;
    ResponsePacket *rpkt = NULL;
    switch(header.packetType)
    {
      //  case NW_PKT_PREPARE:
            //return processPrepare(header, buffer);
         //   break;
        //case NW_PKT_COMMIT:
            //return processCommit(header, buffer);
          //  break;
        case SQL_NW_PKT_CONNECT:
            return processSqlConnect(header, buffer);
            break;
        case SQL_NW_PKT_PREPARE:
            return processSqlPrepare(header, buffer);
            break;
        case SQL_NW_PKT_EXECUTE:
            return processSqlExecute(header, buffer);
            break;
        case SQL_NW_PKT_FETCH:
            return processSqlFetch(header);
            break;
        case SQL_NW_PKT_COMMIT:
            return processSqlCommit(header, buffer);
            break;
        case SQL_NW_PKT_ROLLBACK:
            return processSqlRollback(header, buffer);
            break;
        case SQL_NW_PKT_DISCONNECT:
            conn->rollback();
            rv = conn->disconnect();
            rpkt = new ResponsePacket();
            ptr = (char *) &rpkt->retVal;
            *ptr = 1;
            strcpy(rpkt->errorString, "Success");
            return rpkt;
        case SQL_NW_PKT_FREE:
            return processSqlFree(header, buffer);
            break;
        case SQL_NW_PKT_SHOWTABLES:
            return processSqlShowTables(header, buffer);
            break; 
    }
}
 
void * SqlNetworkHandler::processSqlConnect(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    printDebug(DM_Network, "Processing CONNECT");
    SqlPacketConnect *pkt = new SqlPacketConnect();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    type = (SqlApiImplType) pkt->sqlApiImplType;
    conn = createConnection(type);   
    char *ptr = (char *) &rpkt->retVal;
    DbRetVal rv=conn->connect(pkt->userName, pkt->passWord);
    if (rv != OK) {
        *ptr = 0; 
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        return rpkt;
    }
    if (rv == OK) { 
        *ptr = 1; 
        rv = conn->beginTrans(); 
        return rpkt; 
    }
}

void* SqlNetworkHandler::processSqlPrepare(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    printDebug(DM_Network, "PREPARE %s\n", pkt->stmtString);
    AbsSqlStatement *sqlstmt = createStatement(type);
    sqlstmt->setConnection(conn);
    NetworkStmt *nwStmt = new NetworkStmt();
    nwStmt->stmtID = ++stmtID; 
    printDebug(DM_Network, "Statement string %s\n", pkt->stmtString);
    nwStmt->stmt = sqlstmt;
    DbRetVal rv = sqlstmt->prepare(pkt->stmtString);
    if (rv != OK)
    {
        printError(ErrSysInit, "statement prepare failed\n");
        *retval = 0;
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
        return rpkt;
    }
    int param = sqlstmt->noOfParamFields();
    int proj = sqlstmt->noOfProjFields();
    BindSqlField *bindField = NULL;
    BindSqlProjectField *projField = NULL;
    //populate paramList
    FieldInfo * fInfo = new FieldInfo();
    for (int i = 0; i < param; i++) {
        bindField = new BindSqlField();
        sqlstmt->getParamFldInfo(i + 1, fInfo);
        strcpy(bindField->fName, fInfo->fldName);
        bindField->type = fInfo->type;
        bindField->length = fInfo->length;
        bindField->offset = fInfo->offset;
        strcpy(bindField->defaultValueBuf, fInfo->defaultValueBuf);
        bindField->isNull = fInfo->isNull;
        bindField->isPrimary = fInfo->isPrimary;
        bindField->isDefault = fInfo->isDefault;
        bindField->isUnique = fInfo->isUnique;
        bindField->value = AllDataType::alloc(bindField->type, bindField->length);
        nwStmt->paramList.append(bindField);
    }
    delete fInfo; 
    FieldInfo *fldInfo = new FieldInfo();
    for (int i = 0; i < proj; i++) {
        projField = new BindSqlProjectField();
        sqlstmt->getProjFldInfo(i + 1, fldInfo);
        strcpy(projField->fName, fldInfo->fldName);
        projField->type = fldInfo->type;
        projField->length = fldInfo->length;
        projField->offset = fldInfo->offset;
        strcpy(projField->defaultValueBuf, fldInfo->defaultValueBuf);
        projField->isNull = fldInfo->isNull;
        projField->isPrimary = fldInfo->isPrimary;
        projField->isDefault = fldInfo->isDefault;
        projField->isUnique = fldInfo->isUnique;
        projField->value = AllDataType::alloc(projField->type, projField->length);
        nwStmt->projList.append(projField);
    }
    delete fldInfo; 
    stmtList.append(nwStmt);
    *retval = 1; 
    if(sqlstmt->isSelect()) rpkt->isSelect = true;
    if (param) *(retval+2) = 1;
    if (proj) *(retval+3) = 1;
    rpkt->stmtID = nwStmt->stmtID;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void * SqlNetworkHandler::processSqlExecute(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    SqlPacketExecute *pkt = new SqlPacketExecute();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->setStatementList(stmtList);
    pkt->unmarshall();
    printDebug(DM_Network, "EXECUTE %d\n", pkt->stmtID);
    rpkt->stmtID = pkt->stmtID;
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check the srcNetworkID
       if (stmt->stmtID == pkt->stmtID ) break;
    }
    AbsSqlStatement *sqlstmt = stmt->stmt;
    int rows = 0;
    char *nullInfo = NULL;
    if (pkt->noParams) nullInfo = pkt->getNullInfo();
    for (int i=0; i < pkt->noParams; i++) {
        BindSqlField *bindField = (BindSqlField *) stmt->paramList.get(i+1);
        if (nullInfo[i]) sqlstmt->setNull(i+1);
        else setParamValues(sqlstmt, i+1, bindField->type, bindField->length, (char *)bindField->value);
    }
    //SqlStatement *st = (SqlStatement *)sqlstmt;
    if(sqlstmt->isSelect()) { 
        int noProj = stmt->projList.size();
        for (int i=0; i < noProj; i++) {
            BindSqlProjectField *prjFld = (BindSqlProjectField *) stmt->projList.get(i+1);
            sqlstmt->bindField(i+1, prjFld->value);
        }
    }
    DbRetVal rv = sqlstmt->execute(rows);
    if (rv != OK) { 
        *retval = 0;
        rpkt->errRetVal = rv;
        fillErrorString(rpkt);
      //  delete pkt;
        return rpkt; 
    }
    *retval = 1;
    rpkt->rows = rows;
    strcpy(rpkt->errorString, "Success");
    //delete pkt;
    return rpkt;
}

void * SqlNetworkHandler::processSqlFetch(PacketHeader &header)
{
    //ResponsePacket *rpkt = new ResponsePacket();
    //char *retval = (char *) &rpkt->retVal;
    //SqlPacketFetch *pkt = new SqlPacketFetch();
    //pkt->setBuffer(buffer);
    //pkt->unmarshall();
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    SqlPacketResultSet *rspkt = new SqlPacketResultSet();
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check srcNetworkID
       if (stmt->stmtID == header.stmtID ) break;
    }
    printDebug(DM_Network, "FETCH STMTID: %d", stmt->stmtID);
    AbsSqlStatement *sqlstmt = stmt->stmt;
    void *data=NULL;
    int len=1;
    DbRetVal rv = OK;
    if ((data = sqlstmt->fetch(rv)) != NULL && rv == OK) {
        len = 0;//means record is there
    }
    else if (data == NULL && rv == OK) {
        sqlstmt->close();
        len =1; //end of resultset
    }
    else { 
        len=2;//error
    }
    rspkt->noProjs = stmt->projList.size();
    // set null info for all the fetched field values in projection list
    int nullInfoLen = os::align(rspkt->noProjs);
    char *nullInfo = (char *) malloc(nullInfoLen);
    memset(nullInfo, 0, nullInfoLen);
    char *ptr = nullInfo;
    ListIterator it = stmt->projList.getIterator();
    while (it.hasElement()) {
        BindSqlProjectField *prjFld = (BindSqlProjectField *) it.nextElement();
        if (sqlstmt->isFldNull(prjFld->fName)) *ptr = 1;
        ptr++;
    }
    rspkt->setNullInfo(nullInfo);
    rspkt->setProjList(stmt->projList);
    rspkt->marshall();
    if (rv != OK) { printf("marshall failed\n"); }
    
    if(len == 0) len = rspkt->getBufferSize();
    int numbytes = os::send(sockfd, &len , 4, 0);
    if (len == 1 || len == 2) { ::free (nullInfo); return NULL; }
    int dummy =0;
    numbytes = os::recv(sockfd, &dummy, 4, 0);
    numbytes = os::send(sockfd,rspkt->getMarshalledBuffer(),  
                           rspkt->getBufferSize(), 0);
    if (numbytes == -1) {
       printf("Error in sending the row to the client\n");
       ::free (nullInfo);
       sqlstmt->free();
       delete sqlstmt;
       conn->disconnect();
       exit(1);
    }
    ::free (nullInfo);
    return NULL;
}

void * SqlNetworkHandler::processSqlFree(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    SqlPacketFree *pkt = new SqlPacketFree();
    pkt->setBuffer(buffer);
    pkt->unmarshall();
    rpkt->stmtID = pkt->stmtID;
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check teh srcNetworkID
       if (stmt->stmtID == pkt->stmtID ) break;
    }
    AbsSqlStatement *sqlstmt = stmt->stmt;
    sqlstmt->free();
    ListIterator itprm = stmt->paramList.getIterator();
    BindSqlField *fld = NULL;
    while((fld = (BindSqlField *) itprm.nextElement()) != NULL) delete fld;
    stmt->paramList.reset();
    ListIterator itprj = stmt->projList.getIterator();
    BindSqlProjectField *pfld = NULL;
    while((pfld = (BindSqlProjectField *) itprj.nextElement()) != NULL) delete pfld;       
    stmt->projList.reset();
    delete stmt->stmt;
    stmtList.remove(stmt);
    delete stmt;
    delete pkt;
    *retval = 1;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}


void * SqlNetworkHandler::processSqlCommit(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;
    DbRetVal rv = conn->commit();
    if (rv != OK) {
        *retval = 0;
        strcpy(rpkt->errorString, "Commit failure\n");
        return rpkt;
    }
    rv = conn->beginTrans();
    *retval = 1;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}

void *SqlNetworkHandler::processSqlRollback(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    char *retval = (char *) &rpkt->retVal;

    DbRetVal rv = conn->rollback();
    if (rv != OK) {
        *retval = 0;
        strcpy(rpkt->errorString, "Rollback failure\n");
        return rpkt;
    }
    rv = conn->beginTrans();
    *retval = 1;
    strcpy(rpkt->errorString, "Success");
    return rpkt;
}
/*
void *SqlNetworkHandler::processCommit(PacketHeader &header, char *buffer)
{
    printDebug(DM_Network, "Processing COMMIT");
    PacketCommit *pkt = new PacketCommit();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    List pktList;
    pkt->getExecPacketList(stmtList, pktList);
    DbRetVal rv = applyExecPackets(stmtList, pktList);
    int response = 1;
    if (rv != OK)
    {
         printError(ErrSysFatal, "Unable to apply the exec packets\n");
         response =0;
    }
    return response;

}
void * SqlNetworkHandler::processFree(PacketHeader &header, char *buffer)
{
    PacketFree *pkt = new PacketFree();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    //printf("FREE %d \n", pkt->stmtID);
    int response =1;
    //This wont work for two statement executed in same transaction using same SqlStatement object using free.
    //so do not delete now and put a flag 'readyfordelete' in NetworkStmt object and delete it during execute
//    
    ListIterator iter = stmtList.getIterator();
    NetworkStmt *stmt, *removeStmt = NULL;
    while (iter.hasElement())
    {
       stmt = (NetworkStmt*)iter.nextElement();
       if (stmt->srcNetworkID == header.srcNetworkID
                && stmt->stmtID == pkt->stmtID)
       {
                  removeStmt = stmt;
                  break;
       }
    }
    if (removeStmt) stmtList.remove(removeStmt);
    else printf("Statement id %d not found in list \n",  pkt->stmtID);
    
    return response;
}
void * SqlNetworkHandler::processPrepare(PacketHeader &header, char *buffer) 
{
    PacketPrepare *pkt = new PacketPrepare();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    printDebug(DM_Network, "PREPARE %d %s\n", pkt->stmtID, pkt->stmtString);
    //for (int i =0 ; i < pkt->noParams; i++)
        //printf("PREPARE type %d length %d \n", pkt->type[i], pkt->length[i]);
    int response =1;
    //TODO::add it to the SqlStatement list
    AbsSqlStatement *sqlstmt = SqlFactory::createStatement(type);
    sqlstmt->setConnection(conn);
    NetworkStmt *nwStmt = new NetworkStmt();
    printDebug(DM_Network, "Statement string %s\n", pkt->stmtString);
    nwStmt->srcNetworkID = header.srcNetworkID;
    nwStmt->stmtID =  pkt->stmtID;
    nwStmt->stmt = sqlstmt;
    DbRetVal rv = sqlstmt->prepare(pkt->stmtString);
    if (rv != OK)
    {
        printError(ErrSysInit, "statement prepare failed\n");
        response = 0;
        return response;
    }
    BindSqlField *bindField = NULL;
    //populate paramList
    for (int i = 0; i < pkt->noParams; i++)
    {
             bindField = new BindSqlField();
             bindField->type = (DataType) pkt->type[i];
             bindField->length = pkt->length[i];
             bindField->value = AllDataType::alloc(bindField->type, 
                                                   bindField->length);
             nwStmt->paramList.append(bindField);
    }
    stmtList.append(nwStmt);
    return response;

}

DbRetVal SqlNetworkHandler::applyExecPackets(List sList, List pList)
{
    ListIterator stmtIter = sList.getIterator();
    NetworkStmt *nwstmt;
    DbRetVal rv = conn->beginTrans();
    if (rv != OK) return rv;
    ListIterator pktIter = pList.getIterator();
    PacketExecute *pkt;
    int i = 0;
    BindSqlField *bindField;
    while (pktIter.hasElement())
    {
        pkt = (PacketExecute*) pktIter.nextElement();
        stmtIter.reset();
        bool found = false;
        while (stmtIter.hasElement())
        {
            nwstmt = (NetworkStmt*) stmtIter.nextElement();
            if (nwstmt->stmtID == pkt->stmtID) {found = true ; break;}
        }
        if (!found) {
           printf("stmt not found in list. Negleting unreplicated table...\n"); 
           continue;
        }
        ListIterator paramIter = nwstmt->paramList.getIterator();
        i = 0;
        while (paramIter.hasElement()) {
            bindField = (BindSqlField*) paramIter.nextElement();
            setParamValues(nwstmt->stmt, i+1,  bindField->type, bindField->length, pkt->paramValues[i]);
            i++;
        }
        int rows= 0;
        DbRetVal rv = nwstmt->stmt->execute(rows);
        if (rv != OK )
        {
            printError(ErrSysFatal, "sql execute failed with rv %d\n", rv);
            //TODO::log all things like SQL statements to a file
            SqlNetworkHandler::conn->rollback();
            printError(ErrPeerExecFailed, "Transaction Rolledback\n");
            return ErrPeerExecFailed;
        }
    }
    SqlNetworkHandler::conn->commit();
    return OK;
}
*/
void SqlNetworkHandler::setParamValues(AbsSqlStatement *stmt, int parampos, DataType type,
                    int length, char *value)
{
    switch(type)
    {
        case typeInt:
            stmt->setIntParam(parampos, *(int*)value);
            break;
        case typeLong:
            stmt->setLongParam(parampos, *(long*)value);
            break;
        case typeLongLong:
            stmt->setLongLongParam(parampos, *(long long*)value);
            break;
        case typeShort:
            stmt->setShortParam(parampos, *(short*)value);
            break;
        case typeByteInt:
            stmt->setByteIntParam(parampos, *(char*)value);
            break;
        case typeDouble:
            stmt->setDoubleParam(parampos, *(double*)value);
            break;
        case typeFloat:
            stmt->setFloatParam(parampos, *(float*)value);
            break;
        case typeDate:
            stmt->setDateParam(parampos, *(Date*)value);
            break;
        case typeTime:
            stmt->setTimeParam(parampos, *(Time*)value);
            break;
        case typeTimeStamp:
            stmt->setTimeStampParam(parampos, *(TimeStamp*)value);
            break;
        case typeString:
            {
                char *d =(char*)value;
                d[length-1] = '\0';
                stmt->setStringParam(parampos, (char*)value);
                break;
            }
        case typeBinary:
            stmt->setBinaryParam(parampos, (char *) value, length);
            break; 
    }
    return;
}

AbsSqlConnection * SqlNetworkHandler::createConnection(SqlApiImplType type)
{
    AbsSqlConnection *con = NULL;
    switch(type) {
        case CSqlNetwork:
            con = SqlFactory::createConnection(CSql);
            break;
        case CSqlNetworkAdapter:
            con = SqlFactory::createConnection(CSqlAdapter);
            break;
        case CSqlNetworkGateway:
            con = SqlFactory::createConnection(CSqlGateway);
            break;
        default:
            return NULL;
    }
    return con;
}

AbsSqlStatement * SqlNetworkHandler::createStatement(SqlApiImplType type)
{
    AbsSqlStatement *stmt = NULL;
    switch(type) {
        case CSqlNetwork:
            stmt = SqlFactory::createStatement(CSql);
            break;
        case CSqlNetworkAdapter:
            stmt = SqlFactory::createStatement(CSqlAdapter);
            break;
        case CSqlNetworkGateway:
            stmt = SqlFactory::createStatement(CSqlGateway);
            break;
        default:
            return NULL;
    }
    return stmt;
}

void * SqlNetworkHandler::processSqlShowTables(PacketHeader &header, char *buffer)
{
    ResponsePacket *rpkt = new ResponsePacket();
    rpkt->isSelect = false;
    char *retval = (char *) &rpkt->retVal;
    AbsSqlStatement *sqlstmt = createStatement(type);
    sqlstmt->setConnection(conn);
    DbRetVal rv = OK;
    tableNameList = sqlstmt->getAllTableNames(rv);
    *retval = 1;
    rpkt->stmtID = 0;
    rpkt->rows = tableNameList.size();
    strcpy(rpkt->errorString, "Success");
    delete sqlstmt;
    return rpkt;
}

void SqlNetworkHandler::fillErrorString(ResponsePacket *rpkt)
{
    switch(rpkt->errRetVal) {
        case ErrNoConnection:
            strcpy(rpkt->errorString, "Connection not open.");
            break;
        case ErrUnique:
            strcpy(rpkt->errorString, "Unique constraint violation");
            break;
        case ErrNullViolation:
            strcpy(rpkt->errorString, "Not null constraint violation");
            break;
    }
}
