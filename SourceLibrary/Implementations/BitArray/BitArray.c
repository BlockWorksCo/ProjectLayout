//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "BitArray.h"


//
//  |   0   |   1   |   2   |   3   |   0   |   1
//  012345670123456701234567012345670123456701234567
//  ---xxx---yyy---zzz---aaa---bbb---ccc---ddd---eee
//
//
void BitArraySet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t value )
{
    uint32_t    bitStart            = elementWidth * index;
    uint32_t    bitEnd              = bitStart + elementWidth;
    uint32_t    byteStart           = bitStart / 8;
    uint32_t    bitOffset           = bitStart % 8;
    uint32_t*   elementContainer    = (uint32_t*)&data[byteStart];
    uint32_t    mask                = (1<<(elementWidth+1))-1;
    uint32_t    postionShift        = 32 - (bitOffset*2);
    uint32_t    shiftedMask         = mask << postionShift;

    *elementContainer   = (*elementContainer) & ~shiftedMask;
    *elementContainer   = (*elementContainer) | (value << postionShift);
}



//
//
//
void BitArrayGet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t* value )
{
    uint32_t    bitStart            = elementWidth * index;
    uint32_t    bitEnd              = bitStart + elementWidth;
    uint32_t    byteStart           = bitStart / 8;
    uint32_t    bitOffset           = bitStart % 8;
    uint32_t*   elementContainer    = (uint32_t*)&data[byteStart];
    uint32_t    mask                = (1<<(elementWidth+1))-1;
    uint32_t    postionShift        = 32 - (bitOffset*2);
    uint32_t    shiftedMask         = mask << postionShift;

    *value   = (*elementContainer) >> postionShift;
    *value   = (*value) & mask;
}





