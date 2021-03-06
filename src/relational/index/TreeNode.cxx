/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
  ***************************************************************************/
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<Table.h>
#include<TableImpl.h>
#include<Predicate.h>
#include<PredicateImpl.h>

long long TreeNode::getTotalElements()
{
    DbRetVal rv=OK;
    TreeNode *iter = (TreeNode *) this ;
    TreeNode *tnode=NULL;
    long long totalElement=0;
    while(iter != NULL)
    {
        for(int i=0;i< iter->noElements_;i++)
        {
             tnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))+ ((i)*sizeof(void *))));
             totalElement += tnode->noElements_;
        }
        iter=iter->next_;
    }
    return totalElement;
}

void TreeNode::displayAll(int fldOffset)
{
    DbRetVal rv=OK;
    TreeNode *iter = (TreeNode *) this ;
    TreeNode *tnode=NULL;
    TreeNode *prev = iter;
    bool result = false;
    printf("<TreeNode Info>\n");
    int i=0;
    while(iter != NULL)
    {
        i++;
        tnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))+ ((iter->noElements_-1)*sizeof(void *))));
        char *record = ((char*)tnode->max_)+ fldOffset;
        TreeNode *needremovetnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))));
        printf("  <First level > node:%d noElements:%d </First level>\n",i, iter->noElements_);
        for(int i=0;i< iter->noElements_;i++)
        {
             tnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))+ ((i)*sizeof(void *))));
             printf("    <Second Level Node> Node:%d Elements:%d Min:%d Max:%d </Second Level Node>\n ",i, tnode->noElements_, *(int*)((char*)tnode->min_+fldOffset),  *(int*)((char*)tnode->max_ + fldOffset)); 
             char **rec= (char**)((char*)tnode + sizeof(TreeNode));
             for(int j=0; j < tnode->noElements_; j++){
                 printf("%d,",*((int*)((char*) *(rec + j )+fldOffset)));              
             }
             printf("\n");
             
        }
        iter=iter->next_;
    }
    printf("</TreeNode Info>\n");
}

void TreeNode::displayAll()
{
    DbRetVal rv=OK;
    TreeNode *iter = (TreeNode *) this ;
    TreeNode *tnode=NULL;
    long long totalElement=0;
    int count=1;
    printf("<TreeNode count>\n");
    while(iter != NULL)
    {
        printf("    <First Level Node> %d <Total Elements> %d </Total Elements> <Mutex> %p %d </Mutex></First Level Node>\n", count, iter->noElements_, &iter->mutex_, iter->mutex_.getLockVal()); 
        for(int i=0;i< iter->noElements_;i++)
        {
             tnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))+ ((i)*sizeof(void *))));
             printf("      <Second Level Node %d> %d <Mutex> %p %d</Mutex> </Second Level Node>\n",i, tnode->noElements_, &tnode->mutex_, tnode->mutex_.getLockVal());
             totalElement += tnode->noElements_;
        }
        iter=iter->next_;
        count++;
    }
    printf("  <Total Records> %lld </Total Records>\n",totalElement);
    printf("</TreeNode count>\n");
}

DbRetVal TreeNode::insertNodeIntoFirstLevel(Database * db, IndexInfo * indInfo, void* indexPtr, TreeNode * newNode,int nodepos)
{
    DbRetVal rv=OK;
    TreeNode *start = (TreeNode *) this;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    int offset = info->fldOffset;
    DataType type = info->type;
    int noOfBuckets = info->noOfBuckets;
    char **node = NULL;
    char *tmp = NULL;
    char *tmpnode=NULL;
    TreeNode *tempNode = start;
    if(start->noElements_< noOfBuckets)
    {
        printDebug(DM_TreeIndex,"insertNodeIntoFirstLevel after node insert manage first level node");
        if(start->noElements_<= nodepos)
        {
            node = (char **)((char*)start + sizeof(TreeNode) + (nodepos * sizeof(void *)));
            start->noElements_++;
            *node = (char*)newNode;
        }else
        {
            node = (char**)((char*)start + sizeof(TreeNode));
            tmp = (char *)malloc(sizeof(void *) * (start->noElements_ - nodepos));
            memcpy(tmp, (char*)node + (nodepos * sizeof(void *)), sizeof(void *) * (start->noElements_ - nodepos));
            memcpy((char*)node + ((nodepos+1) * sizeof(void *)), tmp, sizeof(void *) * (start->noElements_ - nodepos));
            free(tmp);
            node = (char **)((char*)node + (nodepos * sizeof(void *)));
            *node = (char*)newNode; 
            start->noElements_++;
        }
    }
    else
    {
        node = (char**)((char*)start + sizeof(TreeNode));
        if(start->noElements_ > nodepos)
        {
            tmpnode = *(char **)((char*)node+ ((start->noElements_-1) * sizeof(void *)));//store last one
            tmp = (char *)malloc(sizeof(void *) * (start->noElements_ - nodepos));
            memcpy(tmp, (char*)node + (nodepos * sizeof(void *)), sizeof(void *) * (start->noElements_ - nodepos-1));
            memcpy((char*)node + ((nodepos+1) * sizeof(void *)), tmp, sizeof(void *) * (start->noElements_ - nodepos-1));
            free(tmp);
            node = (char **)((char*)node + (nodepos * sizeof(void *)));
            *node = (char*)newNode;
        }else
        {
            tmpnode =(char*)newNode;
        }
        nodepos=0;
        if( start->next_ != NULL && start->next_->noElements_< noOfBuckets)
        {
            start = start->next_;
            
            node = (char**)((char*)start + sizeof(TreeNode));
            tmp = (char *)malloc(sizeof(void *) * (start->noElements_ - nodepos));
            memcpy(tmp, (char*)node + (nodepos * sizeof(void *)), sizeof(void *) * (start->noElements_ - nodepos));
            memcpy((char*)node + ((nodepos+1) * sizeof(void *)), tmp, sizeof(void *) * (start->noElements_ - nodepos));
            free(tmp);
            node = (char **)((char*)node + (nodepos * sizeof(void *)));
            *node = (char*)tmpnode;
            start->noElements_++;
            start->mutex_.releaseShareLock(db->procSlot);
        }else
        {
            printDebug(DM_TreeIndex, "Check if full and start->next_ ==NULL then create new one");
            Chunk *ftchunk = (Chunk*) iptr->chunkPtr_;
            TreeNode *ftnode = (TreeNode*) ftchunk->allocate(db, &rv);
            if (ftnode == NULL)
            {
                 printError(rv, "Exit TreeNode firstlevel allocate fail");
                 tempNode->mutex_.releaseShareLock(db->procSlot);
                 return rv;
            }
            ftnode->mutex_.init("TNODE-I");
            ftnode->min_= NULL;
            ftnode->max_ = NULL;
            ftnode->noElements_ =1;
            ftnode->balance_ = 0;
            char **tn=(char**)((char*) ftnode+sizeof(TreeNode));
            *tn = (char*)tmpnode;
            ftnode->next_ = start->next_;
            ftnode->prev_ = start;
            start->next_ = ftnode;
        }
    }
    tempNode->mutex_.releaseShareLock(db->procSlot);
    printDebug(DM_TreeIndex," Mutex Release on %x\n",tempNode);
    return OK;         
}

DbRetVal TreeNode::insertRecordIntoNodeAndArrangeFirstLevel(Database * db, IndexInfo * indInfo, void* indexPtr, void * tuple, TreeNode * fstLevel, int nodePos)
{
    TreeNode *iter = (TreeNode *) this;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    int offset = info->fldOffset;
    DataType type = info->type;
    int noOfBuckets = info->noOfBuckets;
    void *record = NULL;
    char *keyVal = (char*) tuple + info->fldOffset;
    DbRetVal rc = OK;
    bool recordInserted = false;
    TreeNode *tmpNode=NULL;
    int ret = iter->mutex_.getExclusiveLock(db->procSlot);
    if (0 != ret) {
         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
         fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
         return ErrLockTimeOut;
    }
    if(iter->noElements_>= noOfBuckets)
    {
        //Ist level full  
        //Decide new record should go in  left or right of second level
        //if it is inside then create new memcpy all address from location to next node
        //if left check prev_ node has free space or not if yes insert at end else create new
        //if right check next_ node has free space or not if yes insert at Ist loc nad do memcpy else create new
        //create node and link to prevous node and link to the Fistlevel
        record = ((char*)iter->max_)+ info->fldOffset;
        bool result = AllDataType::compareVal(keyVal, record, OpGreaterThan, info->type, info->compLength);
        if(result)
        {
            printDebug(DM_TreeIndex,"locateed Node full new node create at iright"); 
            //check right for free space if not create node right
            tmpNode = iter->next_;  
            if(tmpNode!=NULL && tmpNode->noElements_ < noOfBuckets) 
            {
                //insert at beginning    
                ret = tmpNode->mutex_.getExclusiveLock(db->procSlot);
                if (0 != ret) {
                    printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                    iter->mutex_.releaseShareLock(db->procSlot);
                    fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
                    return ErrLockTimeOut;
                }
                char *tmp = NULL;
                char **rec = (char**)((char*)tmpNode + sizeof(TreeNode));
                tmp = (char *)malloc(sizeof(void *) * (tmpNode->noElements_));
                memcpy(tmp, (char*)rec , sizeof(void *) * (iter->noElements_));
                memcpy((char*)rec + (1*sizeof(void *)), tmp, sizeof(void *) * (iter->noElements_));
                *rec = (char*)tuple;
                tmpNode->min_=tuple;
                tmpNode->noElements_++;   
                free(tmp); 
                iter->mutex_.releaseShareLock(db->procSlot);
                tmpNode->mutex_.releaseShareLock(db->procSlot);
                fstLevel->mutex_.releaseShareLock(db->procSlot);
                printDebug(DM_TreeIndex," Mutex Release on %x\n",fstLevel);
            }
            else
            {
                //allocate new node here
                Chunk *chunk = (Chunk*) iptr->chunkPtr_;
                TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
                if (tnode == NULL)
                {
                    printError(rc, "Exit TreeNode create fail after node full");
                    iter->mutex_.releaseShareLock(db->procSlot);
                    fstLevel->mutex_.releaseShareLock(db->procSlot);
                    printDebug(DM_TreeIndex," Mutex Release on %x\n",fstLevel);
                    return rc;
                }
               if( fstLevel->next_!=NULL && fstLevel->noElements_>= noOfBuckets && fstLevel->next_->noElements_< noOfBuckets)
               {
                    ret = fstLevel->next_->mutex_.getExclusiveLock(db->procSlot);
                    if (0 != ret) {
                        printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                        chunk->free(db, tnode);
                        iter->mutex_.releaseShareLock(db->procSlot);
                        fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
                        return ErrLockTimeOut;
                    }
               }
                tnode->mutex_.init();
                strcpy(tnode->mutex_.name, "Tree");
                tnode->min_ = tuple;
                tnode->max_ = tuple;
                tnode->noElements_ =1;
                tnode->next_ = NULL;
                tnode->prev_ = NULL;
                tnode->balance_ = 0;
                char **rec = (char**)((char*) tnode + sizeof(TreeNode));
                *rec = (char*) tuple;
                if(iter->next_!=NULL){
                     if( 0 !=Mutex::CASL((long*)&iter->next_->prev_, (long)iter->next_->prev_, (long)tnode))
                     {
                          printError(ErrLockTimeOut, "Lock timeout..retry Tree");
                          chunk->free(db, tnode);
                          iter->mutex_.releaseShareLock(db->procSlot);
                          fstLevel->mutex_.releaseShareLock(db->procSlot);
                          return ErrLockTimeOut;
                     }
                }
                tnode->next_= iter->next_;
                tnode->prev_= iter;
                iter->next_= tnode;
                nodePos++;
                iter->mutex_.releaseShareLock(db->procSlot);
                fstLevel->insertNodeIntoFirstLevel(db, indInfo, indexPtr, tnode, nodePos);
            }
        }else
        {
            record = ((char*)iter->min_)+ info->fldOffset;
            bool result = AllDataType::compareVal(keyVal, record, OpLessThan, info->type, info->compLength);
            if(result)
            {
                printDebug(DM_TreeIndex,"\nlocateed Node full new node create at left"); 
                //check left for free space if not create node left
                tmpNode = iter->prev_;
                if(tmpNode!=NULL && tmpNode->noElements_ < noOfBuckets)
                {
                    //insert at End 
                    ret = tmpNode->mutex_.getExclusiveLock(db->procSlot);
                    if (0 != ret) {
                        printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                        iter->mutex_.releaseShareLock(db->procSlot);
                        fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
                        return ErrLockTimeOut;
                    }
                    char **rec = (char**)((char*)tmpNode + sizeof(TreeNode));
                    rec = (char **)((char *)rec + (tmpNode->noElements_ * sizeof(void *)));
                    *rec = (char*)tuple;
                    tmpNode->max_ = tuple;
                    tmpNode->noElements_++;   
                    iter->mutex_.releaseShareLock(db->procSlot);
                    tmpNode->mutex_.releaseShareLock(db->procSlot);
                    fstLevel->mutex_.releaseShareLock(db->procSlot);
                    printDebug(DM_TreeIndex," Mutex Release on %x\n",fstLevel);
                }else
                {
                    //allocate here
                    Chunk *chunk = (Chunk*) iptr->chunkPtr_;
                    TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
                    if (tnode == NULL)
                    {
                         printError(rc, "Exit TreeNode create fail after node full");
                         iter->mutex_.releaseShareLock(db->procSlot);
                         fstLevel->mutex_.releaseShareLock(db->procSlot);
                         printDebug(DM_TreeIndex," Mutex Release on %x\n",fstLevel);
                         return rc;
                    }
                    if( fstLevel->next_!=NULL && fstLevel->noElements_>= noOfBuckets && fstLevel->next_->noElements_< noOfBuckets)
                    {
                         ret = fstLevel->next_->mutex_.getExclusiveLock(db->procSlot);
                         if (0 != ret) {
                             printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                             chunk->free(db, tnode);
                             iter->mutex_.releaseShareLock(db->procSlot);
                             fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
                             return ErrLockTimeOut;
                         }
                    }
                    tnode->mutex_.init();
                    strcpy(tnode->mutex_.name, "Tree");
                    tnode->min_ = tuple;
                    tnode->max_ = tuple;
                    tnode->noElements_ =1;
                    tnode->next_ = NULL;
                    tnode->prev_ = NULL;
                    tnode->balance_ = 0;
                    char **rec = (char**)((char*) tnode + sizeof(TreeNode));
                    printDebug(DM_TreeIndex, "Storing first record at %x\n", rec);
                    *rec = (char*) tuple;
                    if(iter->prev_!=NULL) {
                        if( 0 !=Mutex::CASL((long*)&iter->prev_->next_, (long)iter->prev_->next_, (long)tnode))
                        {
                            printError(ErrLockTimeOut, "Lock timeout..retry Tree");
                            chunk->free(db, tnode);
                            iter->mutex_.releaseShareLock(db->procSlot);
                            fstLevel->mutex_.releaseShareLock(db->procSlot);
                            return ErrLockTimeOut;
                         }
                    }
                    tnode->prev_= iter->prev_;
                    tnode->next_= iter;
                    iter->prev_= tnode;
                    //manage First level
                    iter->mutex_.releaseShareLock(db->procSlot);
                    fstLevel->insertNodeIntoFirstLevel(db, indInfo, indexPtr, tnode, nodePos);
                }
            }else
            {
               //create right
               //locate position shift node
                void *tmprec=NULL;
                char **rec = (char**)((char*) iter + sizeof(TreeNode));
                tmprec = iter->max_; 
                int start = 0;
                int end = iter->noElements_ - 1;
                int middle;
                int loc = 0;
                char *tmp = NULL;
                loc=0;
                for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
                {
                    loc = middle;
                    record = ((char*)*(rec+middle)) + info->fldOffset;
                    printDebug(DM_TreeIndex, "%d-%d\n\n", *((int*)keyVal), *((int*)record));
                    bool res = AllDataType::compareVal(keyVal, record, 
                                      OpLessThan, info->type, info->compLength);
                    if(res)
                    {
                        end = middle - 1;
                    }
                    else
                    {
                        res = AllDataType::compareVal(keyVal, record, 
                                      OpGreaterThan, info->type, info->compLength);
                         if (res) {
                            start = middle + 1;
                            loc = start;
                         }else {
                            loc = middle;
                            if (info->isUnique) {
                               iter->mutex_.releaseShareLock(db->procSlot);
                               fstLevel->mutex_.releaseShareLock(db->procSlot);
                               printError(ErrUnique, "Unique constraint violation");
                               return ErrUnique;
                            }
                            break;
                         }
                    }
                }

                Chunk *chunk = (Chunk*) iptr->chunkPtr_;
                TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rc);
                if (tnode == NULL)
                {
                    printError(rc, "Exit TreeNode create fail after node full");
                    iter->mutex_.releaseShareLock(db->procSlot);
                    fstLevel->mutex_.releaseShareLock(db->procSlot);
                    printDebug(DM_TreeIndex," Mutex Release on %x\n",fstLevel);
                    return rc;
                }
                if( fstLevel->next_!=NULL && fstLevel->noElements_>= noOfBuckets && fstLevel->next_->noElements_< noOfBuckets)
                {
                     ret = fstLevel->next_->mutex_.getExclusiveLock(db->procSlot);
                     if (0 != ret) {
                         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                         chunk->free(db, tnode);
                         iter->mutex_.releaseShareLock(db->procSlot);
                         fstLevel->mutex_.releaseShareLock(db->procSlot);  //release here 1st level
                         return ErrLockTimeOut;
                     }
                }
                tnode->mutex_.init();
                strcpy(tnode->mutex_.name, "Tree");
                tnode->min_ = tuple;
                tnode->max_ = tuple;
                tnode->noElements_ =1;
                tnode->next_ = NULL;
                tnode->prev_ = NULL;
                tnode->balance_ = 0;

                //shift all element from the location to next node
                char **fstRec = (char**)((char*)iter + sizeof(TreeNode));
                tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
                memcpy(tmp, (char*)fstRec+ (loc * sizeof(void *)), sizeof(void *) * (iter->noElements_ - loc));
                rec = (char **)((char*)fstRec + (loc * sizeof(void *)));
                *rec = (char*)tuple;
                //copy to next node
                fstRec = (char**)((char*) tnode + sizeof(TreeNode));
                memcpy((char*)fstRec, tmp, sizeof(void *) * (iter->noElements_- loc));
                free(tmp);
                tnode->noElements_= iter->noElements_- loc;
                tnode->max_= tmprec;
                tnode->min_= *fstRec;
                iter->noElements_= loc + 1;
                iter->max_= tuple;
                if(loc==0)
                {
                    iter->min_ = tuple;
                }
                if(iter->next_!=NULL){
                     if( 0 !=Mutex::CASL((long*)&iter->next_->prev_, (long)iter->next_->prev_, (long)tnode))
                     {
                          printError(ErrLockTimeOut, "Lock timeout..retry Tree");
                          chunk->free(db, tnode);
                          iter->mutex_.releaseShareLock(db->procSlot);
                          fstLevel->mutex_.releaseShareLock(db->procSlot);
                          return ErrLockTimeOut;
                     }
                }
                tnode->next_= iter->next_;
                tnode->prev_=iter;
                iter->next_=tnode; //TODO::need here CASL
                nodePos++;
                //shift right done after this block
                printDebug(DM_TreeIndex,"located Node full new node create at right position %d shift node",loc); 
                //manage First level
                iter->mutex_.releaseShareLock(db->procSlot);
                fstLevel->insertNodeIntoFirstLevel(db, indInfo, indexPtr, tnode, nodePos);
            }
         }
         return OK;
    }
    if(iter->noElements_< noOfBuckets)
    {
        fstLevel->mutex_.releaseShareLock(db->procSlot);
        printDebug(DM_TreeIndex,"located Node not full insert in same node");

        record = ((char*)iter->max_)+ info->fldOffset;
        printDebug(DM_TreeIndex, "\n%d---%d", *((int*)keyVal), *((int*)record));
        bool result = AllDataType::compareVal(keyVal, record, OpGreaterThan, info->type, info->compLength);
        if(result)
        {
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            rec = (char **)((char *)rec + (iter->noElements_ * sizeof(void **)));
            iter->max_ = tuple;
            iter->noElements_++;
            *rec = (char*) tuple;
        }
        else
        {
            int start = 0;
            int end = iter->noElements_ - 1;
            int middle;
            int loc = 0;
            char **rec = (char**)((char*)iter + sizeof(TreeNode));
            char *tmp = NULL;
            loc=0;
            for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
            {
                loc = middle;
                record = ((char*)*(rec+middle)) + info->fldOffset;
                printDebug(DM_TreeIndex, "%d-%d\n\n", *((int*)keyVal), *((int*)record));
                bool res = AllDataType::compareVal(keyVal, record, OpLessThan, info->type, info->compLength);
                if(res)
                {
                    end = middle - 1;
                }
                else
                {
                    res = AllDataType::compareVal(keyVal, record, OpGreaterThan, info->type, info->compLength);
                    if (res) {
                       start = middle + 1;
                       loc = start;
                    }else {
                       loc = middle;
                       if (info->isUnique) 
                       {
                          iter->mutex_.releaseShareLock(db->procSlot);
                          //fstLevel->mutex_.releaseShareLock(db->procSlot);
                          printError(ErrUnique, "Unique constraint violation");
                          return ErrUnique;
                       }
                       break;
                    }
                }
            }
            printDebug(DM_TreeIndex, "\nInsert pos-%d",loc);
            rec = (char**)((char*)iter + sizeof(TreeNode));
            tmp = (char *)malloc(sizeof(void *) * (iter->noElements_ - loc));
            memcpy(tmp, (char*)rec + (loc * sizeof(void *)), sizeof(void *) * (iter->noElements_ - loc));/////////  Check the type cast char *
            memcpy((char*)rec + ((loc+1) * sizeof(void *)), tmp, sizeof(void *) * (iter->noElements_ - loc));
            free(tmp);
            if(loc==0)
            {
                 iter->min_ = tuple;
            }
            iter->noElements_++;
            rec = (char **)((char*)rec + (loc * sizeof(void *)));
            *rec = (char*)tuple;
        }
       //first level mutex release
       iter->mutex_.releaseShareLock(db->procSlot);
    }
    return OK;
}

DbRetVal TreeNode::insert(Database *db,IndexInfo *indInfo,void *indexPtr,void *tuple)
{
    DbRetVal rv=OK;
    TreeNode *iter = (TreeNode *) this ;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    TreeNode *tnode=NULL;
    TreeNode *prev = iter;
    bool result = false;
    DbRetVal  ret = TreeIndex::getTreeNodeMutex(iter, db->procSlot, true);
    if (OK != ret) {
         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
         return ErrLockTimeOut;
    }
    printDebug(DM_TreeIndex," Tree I Level Mutex Taken on %x\n",iter);
    
    while(iter != NULL )
    {
        //get the second level last node as min and max are not stored in first level tree node
        tnode = (TreeNode *)*((char**)((char*)((char*)iter + sizeof(TreeNode))+ ((iter->noElements_-1)*sizeof(void *))));
        char *record = ((char*)tnode->max_)+ info->fldOffset;
        result = AllDataType::compareVal(searchKey, record,OpLessThanEquals,info->type, info->compLength);
         if (result)
         {
             break;
         }else
         {
             if(tnode->noElements_ >= info->noOfBuckets) 
             {
                 if(iter->next_!=NULL)
                 {
                     DbRetVal ret = TreeIndex::getTreeNodeMutex(iter->next_, db->procSlot, true);
                     if (OK != ret) 
                     {
                         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                         iter->mutex_.releaseShareLock(db->procSlot);
                         printDebug(DM_TreeIndex," Tree I Level Mutex Release on %x\n",iter);
                         return ErrLockTimeOut;
                     }
                     printDebug(DM_TreeIndex," Tree I Level Mutex Taken on %x\n",iter->next_);
                     prev = iter;
                     iter = iter->next_;
                     prev->mutex_.releaseShareLock(db->procSlot);
                     printDebug(DM_TreeIndex," Tree I Level Mutex Release on %x\n",prev);
                 }else{
                     prev = iter;
                     iter = iter->next_;
                 }
             }else
             {
                 if(iter->next_!=NULL)
                 {
                     tnode = (TreeNode *)*((char**)((char*)((char*)iter->next_ + sizeof(TreeNode))));
                     char *record = ((char*)tnode->min_)+ info->fldOffset;
                     result = AllDataType::compareVal(searchKey, record,OpLessThan,info->type, info->compLength);
                     if (result)
                     {
                         break;
                     } else 
                     {
                         //if(iter->next_!=NULL)
                         {
                             DbRetVal  ret = TreeIndex::getTreeNodeMutex(iter->next_, 
                                                                          db->procSlot, true);
                             if (OK != ret)
                             {
                                 printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                                 iter->mutex_.releaseShareLock(db->procSlot);
                                 printDebug(DM_TreeIndex," Mutex Release on %x\n",iter);
                                 return ErrLockTimeOut;
                             }
                             printDebug(DM_TreeIndex," Mutex Taken on %x\n",iter);
                             prev = iter;
                             iter = iter->next_;
                             prev->mutex_.releaseShareLock(db->procSlot);
                             printDebug(DM_TreeIndex," Mutex Release on %x\n",prev);
                         }
                         /*else
                         {
                             prev = iter;
                             iter = iter->next_;
                         }*/
                     }
                 }else{
                      break;
                 }
             }
         }
    }    
    //iter will be null if the value being inserted is greater 
    //than the last I-level node's II-level last node's max
    if( iter == NULL && prev->noElements_< info->noOfBuckets)
    {
        iter = prev ;
    }
    if(iter == NULL)
    {
        //TODO::Put this is another function and use the same from 1st record insert
        //create Ist level node  then leaf node ,insert record and return
        printDebug(DM_TreeIndex, "iter =NULL create Ist level node  then leaf node ,insert record and return");
        Chunk *chunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *tnode = (TreeNode*) chunk->allocate(db, &rv);
        if (tnode == NULL)
        {
           printError(rv, "Exit TreeNode allocate fail");
           return rv;
        }
        tnode->mutex_.init();
        strcpy(tnode->mutex_.name, "Tree");
        tnode->min_ = tuple;
        tnode->max_ = tuple;
        tnode->noElements_ =1;
        tnode->next_ = NULL;
        tnode->prev_ = NULL;
        tnode->balance_ = 0;
        char **rec = (char**)((char*) tnode + sizeof(TreeNode));
        printDebug(DM_TreeIndex, "Storing first record at %x\n", rec);
        *rec = (char*) tuple;
        TreeNode *prevNode = (TreeNode*)*(char**)((char*) prev +sizeof(TreeNode)+((prev->noElements_-1)* sizeof(void*)));
        prevNode->next_= tnode;
        tnode->prev_= prevNode;
     //fist levelnode
        Chunk *ftchunk = (Chunk*) iptr->chunkPtr_;
        TreeNode *ftnode = (TreeNode*) ftchunk->allocate(db, &rv);
        if (ftnode == NULL)
        {
            printDebug(DM_TreeIndex, "Exit TreeNode firstlevel allocate fail");
            return rv;
        }
        ftnode->mutex_.init("TNODE-I");
        ftnode->min_= NULL;
        ftnode->max_ = NULL;
        ftnode->noElements_ =1;
        ftnode->next_ = NULL;
        ftnode->balance_ = 0;
        char **tn=(char**)((char*) ftnode+sizeof(TreeNode));
        *tn = (char*)tnode;
        ftnode->prev_= prev;
        prev->next_=ftnode;
        prev->mutex_.releaseShareLock(db->procSlot);
        printDebug(DM_TreeIndex," Mutex Release on %x\n",prev);
        return OK;
    }
    //Get second level node and node position from the 
    //first level node identified above as 'iter'
    int nodepos=0;
    tnode = locateNodeFromFirstLevel(iter, indInfo, tuple, &nodepos);
    //first level mutex is taken and it is released in the below function
    //This is because in case arrangement in first level node when it is full 
    //then subsequent first level node mutex is taken and current first level node 
    //mutex is released
    rv = tnode->insertRecordIntoNodeAndArrangeFirstLevel(db, indInfo, indexPtr, tuple, iter, nodepos);
    return rv;
}

TreeNode* TreeNode::locateNode(Database *db, TreeNode *iter, void *tuple, IndexInfo *indInfo,DbRetVal &rv)
{
    if(iter == NULL) return NULL;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    TreeNode *tnode=NULL;
    DbRetVal  ret = TreeIndex::getTreeNodeMutex(iter, db->procSlot, true);
    if (OK != ret) {
         printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
         rv = ErrLockTimeOut;
         return NULL;
    }
    printDebug(DM_TreeIndex," Mutex Taken on %x\n",iter);
    TreeNode *tmpNode=NULL;
    while(iter->noElements_>= info->noOfBuckets && iter != NULL)
    {
        tnode = (TreeNode *)*((char**)((char*)iter + sizeof(TreeNode)+ ((iter->noElements_-1)*sizeof(void *))));
        char *record = ((char*)tnode->max_)+ info->fldOffset;
        bool result = AllDataType::compareVal(searchKey, record,OpLessThanEquals,info->type, info->compLength);
        if (result)
        {
            break;
        }else
        {
            if(iter->next_!=NULL)
            {
                DbRetVal  ret = TreeIndex::getTreeNodeMutex(iter->next_, db->procSlot, true);
                if (OK != ret) 
                {
                    printError(ErrLockTimeOut,"Unable to lock the tree node. Retry...");
                    iter->mutex_.releaseShareLock(db->procSlot);    
                    printDebug(DM_TreeIndex," Mutex Release on %x\n",iter);
                    rv = ErrLockTimeOut;
                    return NULL;
                }
                printDebug(DM_TreeIndex," Mutex Taken on %x\n",iter->next_);
                tmpNode = iter;
                iter = iter->next_;
                tmpNode->mutex_.releaseShareLock(db->procSlot);
                printDebug(DM_TreeIndex," Mutex Release on %x\n",tmpNode);
            }else{
                iter->mutex_.releaseShareLock(db->procSlot);
                printDebug(DM_TreeIndex," Mutex Release on %x\n",iter);
                iter = iter->next_;
            }
        }
    }
    //Get leaf Node
    return iter;
   
}

TreeNode *TreeNode::locateNodeFromFirstLevel(TreeNode *ftnode, IndexInfo *indInfo,void *tuple, int *pos)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    int fldOffset = info->fldOffset;
    DataType type = info->type;
    int length = info->compLength;
    void *searchKey =(void*)((char*)tuple + info->fldOffset);
    int loc=0, middle = 0, start = 0, end = ftnode->noElements_-1;
    char **node = (char**)((char*)ftnode + sizeof(TreeNode));
   TreeNode *tNode;
   for(middle = (start + end) / 2; start <= end ; middle = (start +end )/2)
    {
        loc = middle;
        char *record =(char *)(((TreeNode *) *(char**)((char*)node + (loc * sizeof(void *))))->max_)+fldOffset;

        bool res = AllDataType::compareVal(searchKey, record, OpLessThan,type, length);
        if(res)
        {
            end = middle - 1;
        }
        else
        {
            res = AllDataType::compareVal(searchKey, record, OpGreaterThan, type, length);
            if (res) {
                start = middle + 1;
                if(start <= (ftnode->noElements_-1)) loc = start;
            }else {
                loc=middle;
                break;
            }
        }
    }
    printDebug(DM_TreeIndex, "inside locateNodeFromFirstLevel loc=%d",loc);
    *pos=loc;
    tNode = ((TreeNode *)*(char**)((char*)node + (loc * sizeof(void *))));
    return  tNode;
}
