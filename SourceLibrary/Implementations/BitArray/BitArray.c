


#include "BitArray.h"


//
//
//
void BitArraySet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t value )
{
    uint32_t    bitStart            = elementWidth * index;
    uint32_t    bitEnd              = bitStart + elementWidth;
    uint32_t    byteStart           = bitStart / 8;
    uint32_t    bitOffset           = bitStart % 8;
    uint32_t*   elementContainer    = (uint32_t*)&data[byteStart];
}



//
//
//
void BitArrayGet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t* value )
{
    uint32_t    bitStart    = elementWidth * index;
    uint32_t    bitEnd      = bitStart + elementWidth;

}





