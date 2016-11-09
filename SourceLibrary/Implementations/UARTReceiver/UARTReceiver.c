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
PRIVATE bool        idle            = true;


//
//
//
void ResetUARTReceiver()
{
    sampleNumber    = 0;
    highCount       = 0;
    bitCount        = 0;
    idle            = true;
}


//
//
//
void ReceivedFullByte()
{
    DebugPrintf("<Received Byte %02x>\n", receivedByte);

    ResetUARTReceiver();
}


//
//
//
void ReceivedHighBit()
{
    DebugPrintf("  b%d <High>\n", bitCount);

    if( bitCount == 0 )
    {
        startBit    = true;
    }

    if( (bitCount >= 1) && (bitCount < 9) )
    {
        receivedByte    >>= 1;
        receivedByte    |= 0x80;
    }

    if( bitCount == 9 )
    {
        stopBit    = true;

        //
        // If the startBit is low and the stopBit is high, we've received a full byte.'
        //
        if(startBit == false)
        {
            DebugPrintf("Stop Bit detected\n");
            ReceivedFullByte();
        }
    }

    bitCount++;
}

void ReceivedLowBit()
{
    DebugPrintf("  b%d <Low>\n", bitCount);

    if( bitCount == 0 )
    {
        startBit    = false;
    }

    if( (bitCount >= 1) && (bitCount < 9) )
    {
        receivedByte    >>= 1;
    }

    if( bitCount == 9 )
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
    bool    currentState    = GET_RX_STATE();

    if( idle == true )
    {
        //
        // We've not received a start bit yet.
        //
        if( currentState == false)
        {
            //
            // We received a low bit while in idle, this is the start bit.
            //
            idle    = false;
            DebugPrintf("\nStart Bit detected\n");
            bitCount    = 0;
        }
    }

    //
    // If we are no longer idle, then process the byte.
    //
    if( idle == false )
    {
        //
        // We've received a start bit.
        //
        switch(sampleNumber)
        {
            case 0:
            {
                if(currentState == true)
                {
                    highCount++;
                }
                sampleNumber    = 1;
                break;
            }

            case 1:
            {
                if(currentState == true)
                {
                    highCount++;
                }
                sampleNumber    = 2;
                break;
            }

            case 2:
            {
                if(currentState == true)
                {
                    highCount++;
                }
                sampleNumber    = 3;
                break;
            }


            case 3:
            {
                if(currentState == true)
                {
                    highCount++;
                }

                //
                // We've received a bit, process it...
                //
                DebugPrintf("  %d/4 ",highCount);
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
}



uint8_t GetUARTReceivedByte()
{
    if( idle == true)
    {
        return receivedByte;
    }
    else
    {
        return 0x00;
    }
}



