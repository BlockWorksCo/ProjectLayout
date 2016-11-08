//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "UARTReceiver.h"
#include "ErrorHandling.h"
#include "DebugText.h"


PRIVATE uint32_t    sampleNumber    = 0;
PRIVATE uint32_t    highCount       = 0;
PRIVATE uint32_t    bitCount        = 0;
PRIVATE uint8_t     receivedByte    = 0x00;
PRIVATE bool        startBit        = false;
PRIVATE bool        stopBit         = false;


//
//
//
void ResetUARTReceiver()
{
    sampleNumber    = 0;
    highCount       = 0;
    bitCount        = 0;
}


//
//
//
void ReceivedHighBit()
{
    DebugPrintf("%d <High>\n", bitCount);

    if( bitCount == 0 )
    {
        startBit    = true;
    }

    if( (bitCount >= 1) && (bitCount < 9) )
    {
        receivedByte    <<= 1;
        receivedByte    |= 0x01;
    }

    if( bitCount == 8 )
    {
        stopBit    = true;
    }

    bitCount++;
}

void ReceivedLowBit()
{
    DebugPrintf("%d <Low>\n", bitCount);

    if( bitCount == 0 )
    {
        startBit    = false;
    }

    if( (bitCount >= 1) && (bitCount < 8) )
    {
        receivedByte    <<= 1;
    }

    if( bitCount == 8 )
    {
        stopBit    = false;
    }

    bitCount++;
}


//
//
//
void UARTReceiveHandler()
{
    //
    //
    //
    switch(sampleNumber)
    {
        case 0:
        {
            if(GET_RX_STATE() == true)
            {
                highCount++;
            }
            sampleNumber    = 1;
            break;
        }

        case 1:
        {
            if(GET_RX_STATE() == true)
            {
                highCount++;
            }
            sampleNumber    = 2;
            break;
        }

        case 2:
        {
            if(GET_RX_STATE() == true)
            {
                highCount++;
            }
            sampleNumber    = 3;
            break;
        }


        case 3:
        {
            if(GET_RX_STATE() == true)
            {
                highCount++;
            }

            //
            //
            //
            if( highCount >= 3 )
            {
                ReceivedHighBit();
            }
            else
            {
                ReceivedLowBit();
            }

            highCount       = 0;
            sampleNumber    = 0;

            break;
        }

        default:
        {
            PANIC();
        }
    }

}



uint8_t GetUARTReceivedByte()
{
    return receivedByte;
}



