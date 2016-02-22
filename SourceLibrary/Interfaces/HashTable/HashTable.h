//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__



#include "Common.h"



#define HASH_TABLE_SIZE                 (16)
#define HASH_TABLE_MAX_COLLISIONS       (16)


//
//
//
//typedef void        (*HashTableValue);
typedef uint32_t    HashTableValue;

//
//
//
typedef uint32_t HashTableKey;




typedef struct
{
    HashTableKey    key;
    HashTableValue  value;
    bool            usedFlag;

} HashTableEntry;


void HashTablePut( HashTableKey key, HashTableValue value );
HashTableValue HashTableGet( HashTableKey key, HashTableValue failValue );



#endif


