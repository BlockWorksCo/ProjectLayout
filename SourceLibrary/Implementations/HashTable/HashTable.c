//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "HashTable.h"
#include "ErrorHandling.h"


HashTableEntry  table[HASH_TABLE_SIZE][HASH_TABLE_MAX_COLLISIONS]   = {0};


//
//
//
uint32_t HashFunction( HashTableKey key )
{
    uint32_t    index   = key % HASH_TABLE_SIZE;
    return index;
}


//
//
//
void HashTablePut( HashTableKey key, HashTableValue value )
{
    uint32_t    index   = HashFunction( key );

    for(uint32_t i=0; i<HASH_TABLE_MAX_COLLISIONS; i++)
    {
        if( table[index][i].usedFlag == false )
        {
            table[index][i].usedFlag = true;
            table[index][i].key         = key;
            table[index][i].value       = value;
            return;
        }
    }

    PANIC();
}


//
//
//
HashTableValue HashTableGet( HashTableKey key, HashTableValue failValue )
{
    uint32_t    index   = HashFunction( key );

    for(uint32_t i=0; i<HASH_TABLE_MAX_COLLISIONS; i++)
    {
        if( (table[index][i].key      == key ) && 
            (table[index][i].usedFlag == true) )
        {
            return table[index][i].value;
        }
    }

    return failValue;
}




