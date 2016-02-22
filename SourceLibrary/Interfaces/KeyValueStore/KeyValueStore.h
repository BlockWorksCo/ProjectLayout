//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __KEYALUESTORE_H__
#define __KEYALUESTORE_H__

#include "Common.h"
#include "Utilities.h"


#define DECLARE_KEY_VALUE_STORAGE( type, name )     type name##Storage
#define DECLARE_KEY( name )                         name = offsetof( KeyValueData, name##Storage )
#define SET_KEY_VALUE( key, value )                 if(KeyValueValidate(key) == true) keyValueData.key##Storage = value;KeyValueStoreWritten(key)
#define GET_KEY_VALUE( key )                        keyValueData.key##Storage 

typedef struct
{
    DECLARE_KEY_VALUE_STORAGE( uint32_t, Value1 );
    DECLARE_KEY_VALUE_STORAGE( uint32_t, Value2 );
    DECLARE_KEY_VALUE_STORAGE( uint32_t, Value3 );
    DECLARE_KEY_VALUE_STORAGE( uint32_t, Value4 );
    DECLARE_KEY_VALUE_STORAGE( uint32_t, Value5 );

} KeyValueData;


extern KeyValueData keyValueData;

typedef enum
{
    DECLARE_KEY( Value1 ),
    DECLARE_KEY( Value2 ),
    DECLARE_KEY( Value3 ),
    DECLARE_KEY( Value4 ),
    DECLARE_KEY( Value5 ),

    MaxKeyValue = sizeof(KeyValueData)

} Key;


void KeyValueStoreWritten( Key key );
bool KeyValueValidate( Key key, void* _value )

#endif



