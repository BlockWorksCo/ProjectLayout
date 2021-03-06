//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Utilities.h"







typedef enum
{
    Idle,
    StartCondition,
    StartConditionEnd,
    Bit7,
    Bit7End,
    Bit6,
    Bit6End,
    Bit5,
    Bit5End,
    Bit4,
    Bit4End,
    Bit3,
    Bit3End,
    Bit2,
    Bit2End,
    Bit1,
    Bit1End,
    Bit0,
    Bit0End,

    ReadBit7,
    ReadBit7End,
    ReadBit6,
    ReadBit6End,
    ReadBit5,
    ReadBit5End,
    ReadBit4,
    ReadBit4End,
    ReadBit3,
    ReadBit3End,
    ReadBit2,
    ReadBit2End,
    ReadBit1,
    ReadBit1End,
    ReadBit0,
    ReadBit0End,

    Ack,
    AckEnd,
    StopCondition,
    StopConditionEnd,

} I2CMasterState;




void WriteEngine();
void ReadEngine();
void StopEngine();



typedef enum
{
    Transmitting,
    Receiving,
    Stopping,
    Stopped,

} I2CMasterTransferState;


#define    maxBytesToTransmit 64

I2CMasterTransferState  masterState                         = Stopped;
uint32_t                nextEdgeTime                        = 0;
bool                    nextValue                           = 0;
I2CAddress              address                             = 0;
uint8_t                 dataToTransmit[maxBytesToTransmit]  = {0};
uint8_t                 acksForBytes[maxBytesToTransmit]    = {0};
uint8_t                 numberOfBytesToTransfer             = 0;
I2CMasterState          state                               = 0;
bool                    transferFinished                    = true;
uint8_t*                bytes                               = 0;
uint8_t                 currentByteToTransmit               = 0;
uint8_t                 currentByteBeingReceived            = 0;
uint32_t                currentDataByteIndex                = 0;

            extern uint32_t cycleCount;


//
//
//
void ResetI2CMaster()
{
    SET_SDA();
    SET_SCL();
    masterState     = Stopped;
    state           = Idle;
}




//
//
//
void I2CWrite( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes )
{
    masterState         = Transmitting;
    state               = StartCondition;

    address                 = _address;
    numberOfBytesToTransfer = _numberOfBytes;
    bytes                   = _bytes;

    currentByteToTransmit   = address & (~0x1);
    currentDataByteIndex    = 0;
}


//
//
//
void I2CRead( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes )
{
    masterState             = Receiving;
    state                   = StartCondition;

    address                 = _address;
    numberOfBytesToTransfer = _numberOfBytes;
    bytes                   = _bytes;

    currentByteToTransmit   = address | (0x1);
    currentDataByteIndex    = 0;

    currentByteBeingReceived    = 0;
}


//
//
//
void Stop()
{
    masterState         = Stopping;
    state               = StartCondition;
}












void SetSDAAsPerData( bool data )
{
    if(data == true)
    {
        SET_SDA();
    }
    else
    {
        CLEAR_SDA();
    }
}


//
// Called at regular intervals to transmit an I2C bus protocol.
//
void WriteEngine()
{
    switch(state)
    {
        case StartCondition:
        {
            CLEAR_SDA();    // Start condition.
            state   = StartConditionEnd;
            break;
        }

        case StartConditionEnd:
        {
            CLEAR_SCL();    // Start condition.
            state   = Bit7;
            break;
        }

        case Bit7:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 7) & 0x01 );    // b7
            SET_SCL();
            bool clkValue = GET_SCL();

            if(clkValue == true)
            {
                currentByteBeingReceived    = 0;
                state   = Bit7End;
            }
            else
            {
                DebugPrintf("<stretch @%d>\n", cycleCount);
                //
                // Clock stretching situation, slave is holding it low.
                //
                state   = Bit7;
            }
            
            break;
        }

        case Bit7End:
        {
            CLEAR_SCL();
            state   = Bit6;
            break;
        }

        case Bit6:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 6) & 0x01 );    // b6
            SET_SCL();
            state   = Bit6End;
            break;
        }

        case Bit6End:
        {
            CLEAR_SCL();
            state   = Bit5;
            break;
        }

        case Bit5:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 5) & 0x01 );    // b5
            SET_SCL();
            state   = Bit5End;
            break;
        }

        case Bit5End:
        {
            CLEAR_SCL();
            state   = Bit4;
            break;
        }

        case Bit4:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 4) & 0x01 );    // b4
            SET_SCL();
            state   = Bit4End;
            break;
        }

        case Bit4End:
        {
            CLEAR_SCL();
            state   = Bit3;
            break;
        }

        case Bit3:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 3) & 0x01 );    // b3
            SET_SCL();
            state   = Bit3End;
            break;
        }

        case Bit3End:
        {
            CLEAR_SCL();
            state   = Bit2;
            break;
        }

        case Bit2:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 2) & 0x01 );    // b2
            SET_SCL();
            state   = Bit2End;
            break;
        }

        case Bit2End:
        {
            CLEAR_SCL();
            state   = Bit1;
            break;
        }

        case Bit1:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 1) & 0x01 );    // b1
            SET_SCL();
            state   = Bit1End;
            break;
        }

        case Bit1End:
        {
            CLEAR_SCL();
            state   = Bit0;
            break;
        }

        case Bit0:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 0) & 0x01 );    // b0
            SET_SCL();
            state   = Bit0End;
            break;
        }

        case Bit0End:
        {
            CLEAR_SCL();
            state   = Ack;
            break;
        }

        case Ack:
        {
            SET_SDA();
            SET_SCL();      // ACK bit should be set by device now.
            state   = AckEnd;
            break;
        }

        case AckEnd:
        {
            extern uint32_t cycleCount;
            bool ackValue = GET_SDA(); // TODO: Get ACK bit.
            CLEAR_SCL();

            if( (currentDataByteIndex < numberOfBytesToTransfer) && (ackValue == false) )
            {
                currentByteToTransmit   = bytes[currentDataByteIndex];
                currentDataByteIndex++;
                state   = Bit7;
            }
            else
            {
                state   = StopCondition;
                I2C_OPERATION_COMPLETE();
            }
            break;
        }


        case StopCondition:
        {
            CLEAR_SDA();
            SET_SCL();                          // stop condition
            // TODO: Get ACK bit.
            state   = StopConditionEnd;
            break;
        }

        case StopConditionEnd:
        {
            SET_SDA();
            SET_SCL();                          // stop condition
            masterState     = Stopped;
            state   = Idle;
            break;
        }

        default:
        {
            PANIC();
            break;
        }
    }

}

//
// Called at regular intervals to receive an I2C bus protocol message.
//
void ReadEngine()
{
    switch(state)
    {
        case StartCondition:
        {
            CLEAR_SDA();    // Start condition.
            state   = StartConditionEnd;
            break;
        }

        case StartConditionEnd:
        {
            CLEAR_SCL();    // Start condition.
            state   = Bit7;
            break;
        }

        case Bit7:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 7) & 0x01 );    // b7
            SET_SCL();
            state   = Bit7End;
            break;
        }

        case Bit7End:
        {
            CLEAR_SCL();
            state   = Bit6;
            break;
        }

        case Bit6:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 6) & 0x01 );    // b6
            SET_SCL();
            state   = Bit6End;
            break;
        }

        case Bit6End:
        {
            CLEAR_SCL();
            state   = Bit5;
            break;
        }

        case Bit5:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 5) & 0x01 );    // b5
            SET_SCL();
            state   = Bit5End;
            break;
        }

        case Bit5End:
        {
            CLEAR_SCL();
            state   = Bit4;
            break;
        }

        case Bit4:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 4) & 0x01 );    // b4
            SET_SCL();
            state   = Bit4End;
            break;
        }

        case Bit4End:
        {
            CLEAR_SCL();
            state   = Bit3;
            break;
        }

        case Bit3:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 3) & 0x01 );    // b3
            SET_SCL();
            state   = Bit3End;
            break;
        }

        case Bit3End:
        {
            CLEAR_SCL();
            state   = Bit2;
            break;
        }

        case Bit2:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 2) & 0x01 );    // b2
            SET_SCL();
            state   = Bit2End;
            break;
        }

        case Bit2End:
        {
            CLEAR_SCL();
            state   = Bit1;
            break;
        }

        case Bit1:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 1) & 0x01 );    // b1
            SET_SCL();
            state   = Bit1End;
            break;
        }

        case Bit1End:
        {
            CLEAR_SCL();
            state   = Bit0;
            break;
        }

        case Bit0:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 0) & 0x01 );    // b0
            SET_SCL();
            state   = Bit0End;
            break;
        }

        case Bit0End:
        {
            CLEAR_SCL();
            state   = Ack;
            break;
        }

        case Ack:
        {
            SET_SDA();
            SET_SCL();
            state   = AckEnd;
            break;
        }

        case AckEnd:
        {
            bool ackValue = GET_SDA();
                DebugPrintf("<ACK=%d @%d>\n", ackValue, cycleCount);

                CLEAR_SCL();
                if( (currentDataByteIndex < numberOfBytesToTransfer) && (ackValue == false) )
                {
                    currentDataByteIndex++;
                    state   = ReadBit7;
                }
                else
                {
                    state   = StopCondition;
                    I2C_OPERATION_COMPLETE();                    
                }

            break;
        }






        case ReadBit7:
        {
            bool clkValue = GET_SCL();
            SET_SCL();

            if(clkValue == true)
            {
                currentByteBeingReceived    = 0;
                state   = ReadBit7End;
            }
            else
            {
                DebugPrintf("<stretch @%d>\n", cycleCount);
                //
                // Clock stretching situation, slave is holding it low.
                //
                state   = ReadBit7;
            }
            break;
        }

        case ReadBit7End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 7);

            CLEAR_SCL();
            state   = ReadBit6;
            break;
        }


        case ReadBit6:
        {
            SET_SCL();
            state   = ReadBit6End;
            break;
        }

        case ReadBit6End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 6);

            CLEAR_SCL();
            state   = ReadBit5;
            break;
        }



        case ReadBit5:
        {
            SET_SCL();
            state   = ReadBit5End;
            break;
        }

        case ReadBit5End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 5);

            CLEAR_SCL();
            state   = ReadBit4;
            break;
        }



        case ReadBit4:
        {
            SET_SCL();
            state   = ReadBit4End;
            break;
        }

        case ReadBit4End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 4);

            CLEAR_SCL();
            state   = ReadBit3;
            break;
        }



        case ReadBit3:
        {
            SET_SCL();
            state   = ReadBit3End;
            break;
        }

        case ReadBit3End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 3);

            CLEAR_SCL();
            state   = ReadBit2;
            break;
        }




        case ReadBit2:
        {
            SET_SCL();
            state   = ReadBit2End;
            break;
        }

        case ReadBit2End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 2);

            CLEAR_SCL();
            state   = ReadBit1;
            break;
        }




        case ReadBit1:
        {
            SET_SCL();
            state   = ReadBit1End;
            break;
        }

        case ReadBit1End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 1);

            CLEAR_SCL();
            state   = ReadBit0;
            break;
        }




        case ReadBit0:
        {
            SET_SCL();
            state   = ReadBit0End;
            break;
        }

        case ReadBit0End:
        {
            bool value = GET_SDA(); 
            currentByteBeingReceived    |= ((value&0x01) << 0);

            CLEAR_SCL();
            state   = Ack;
            //DebugPrintf("readbyte complete... going back to Ack state (%d)\n",cycleCount);
            I2C_BYTE_RECEIVED( currentByteBeingReceived );

            break;
        }




        case StopCondition:
        {
            CLEAR_SDA();
            SET_SCL();                          // stop condition
            // TODO: Get ACK bit.
            state   = StopConditionEnd;
            break;
        }

        case StopConditionEnd:
        {
            SET_SDA();
            SET_SCL();                          // stop condition
            masterState     = Stopped;
            state   = Idle;
            break;
        }

        default:
        {
            PANIC();
            break;
        }
    }
}


//
// Called at regular intervals to transmit an I2C bus protocol.
//
void StopEngine()
{
    const uint8_t   numberOfStartStates     = 3;
    const uint8_t   numberOfStopStates      = 3;
    const uint8_t   numberOfBitsPerByte     = 8+1;                      // data+ACK.
    const uint8_t   numberOfStatesPerByte   = numberOfBitsPerByte*2;    // lo clock & hi clock.

    if( state == 0 )
    {
        //
        // Stop condition 0
        //
        CLEAR_SCL();
        CLEAR_SDA();
    }
    else if( state == 1 )
    {
        //
        // Stop condition 1
        //
        SET_SCL();
    }
    else if( state == 2 )
    {
        //
        // Stop condition 2
        //
        SET_SDA();
    }
    else
    {
        //
        // No more.
        //
        SET_SDA();
        SET_SCL();
        transferFinished = true;

        //Call( completionEvent );
        masterState     = Stopped;
    }

    state++;
}









//
//
//
void I2CMasterHandler()
{
    switch( masterState )
    {
        case Transmitting:
            WriteEngine();
            break;

        case Receiving:
            ReadEngine();
            break;

        case Stopping:
            StopEngine();
            break;

        case Stopped:
            break;

        default:
            PANIC();
            break;
    }

}


