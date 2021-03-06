Case 1: With -d option before table creation:
============================================
<Database Usage Statistics>
<DatabaseStatistics>
  <Database Name>  SYSTEMDB </Database Name>
  <Max Size> 1048576 </Max Size>
  <First Page> 17d7c000 </First Page>
  <Total Pages> 111 </Total Pages>
  <Used Normal Pages> 13 </Used Normal Pages>
  <Used Merged Pages> 2 </Used Merged Pages>
  <Chunks Used> 15 </Chunks Used>
</DatabaseStatistics>
<ProcTable>
  <UsedSlots> 1 </UsedSlots>
  <FreeSlots> 99 </FreeSlots>
</ProcTable>
<TransactionTable>
  <UsedSlots> 0 </UsedSlots>
  <FreeSlots> 100 </FreeSlots>
  <UndoLogs>
    <TotalNodes> 0 </TotalNodes>
  </UndoLogs>
</TransactionTable>
<LockTable>
  <TotalBuckets> 2048  </TotalBuckets>
  <UsedBuckets> 0  </UsedBuckets>
  <TotalLockNodes> 0  </TotalLockNodes>
</LockTable>
<DatabaseStatistics>
  <Database Name>  userdb </Database Name>
  <Max Size> 10485760 </Max Size>
  <First Page> 17e7a000 </First Page>
  <Total Pages> 1279 </Total Pages>
  <Used Normal Pages> 0 </Used Normal Pages>
  <Used Merged Pages> 0 </Used Merged Pages>
  <Chunks Used> 0 </Chunks Used>
</DatabaseStatistics>
</Database Usage Statistics>
Case 2: With -D chunk option after table creation:
============================================
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 4 </TotalDataNodes> 
                <SizeOfDataNodes> 116 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 65540 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 24 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 4 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TransHasTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 12 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 5 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UndoLogTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 0 </SizeOfDataNodes> 
                <Allocation Type> VariableSizeAllocator </Allocation Type>
        <Chunk Id> 10 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > DatabaseTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 84 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 92 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 144 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 104 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 17 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 76 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 18 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 101 </Chunk Id> 
                <TotalPages> 1250 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 4999 </TotalDataNodes> 
                <SizeOfDataNodes> 2020 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 102 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 32292 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 103 </Chunk Id> 
                <TotalPages> 10 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 4999 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 104 </Chunk Id> 
                <TotalPages> 6 </TotalPages> 
                <ChunkName >  </ChunkName> 
                <TotalDataNodes> 6 </TotalDataNodes> 
                <SizeOfDataNodes> 4092 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
Statement Executed: Rows Affected = 3999
Case 3: With -D chunk  option after record deleted:
===================================================
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 4 </TotalDataNodes> 
                <SizeOfDataNodes> 116 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 65540 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 24 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 4 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TransHasTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 12 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 5 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UndoLogTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 0 </SizeOfDataNodes> 
                <Allocation Type> VariableSizeAllocator </Allocation Type>
        <Chunk Id> 10 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > DatabaseTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 84 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 92 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 144 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 104 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 17 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 76 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 18 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 101 </Chunk Id> 
                <TotalPages> 1250 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 1000 </TotalDataNodes> 
                <SizeOfDataNodes> 2020 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 102 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 32292 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 103 </Chunk Id> 
                <TotalPages> 10 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 1000 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 104 </Chunk Id> 
                <TotalPages> 6 </TotalPages> 
                <ChunkName >  </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 4092 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
Statement Executed: Rows Affected = 0
Case 4: With -D chunk  option after compact statement :
=======================================
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 4 </TotalDataNodes> 
                <SizeOfDataNodes> 116 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 65540 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 24 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 4 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TransHasTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 12 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 5 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UndoLogTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 0 </SizeOfDataNodes> 
                <Allocation Type> VariableSizeAllocator </Allocation Type>
        <Chunk Id> 10 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > DatabaseTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 84 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 92 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 144 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 104 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 17 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 76 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 18 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 101 </Chunk Id> 
                <TotalPages> 252 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 1000 </TotalDataNodes> 
                <SizeOfDataNodes> 2020 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 102 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 32292 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 103 </Chunk Id> 
                <TotalPages> 4 </TotalPages> 
                <ChunkName > t1_idx1_Primary </ChunkName> 
                <TotalDataNodes> 1000 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 104 </Chunk Id> 
                <TotalPages> 4 </TotalPages> 
                <ChunkName >  </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 4092 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
echo  drop table t1;
Statement Executed
