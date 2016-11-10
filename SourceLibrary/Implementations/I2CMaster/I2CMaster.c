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
uint32_t                currentDataByteIndex                = 0;



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
    numberOfBytesToTransfer = _numberOfBytes;
    masterState             = Receiving;
    state                   = StartCondition;
    address                 = _address;
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
            SET_SCL();      // ACK bit should be set by device now.
            state   = AckEnd;
            break;
        }

        case AckEnd:
        {
            CLEAR_SCL();
            bool ackValue = GET_SDA(); // TODO: Get ACK bit.

            if(currentDataByteIndex < numberOfBytesToTransfer)
            {
                currentByteToTransmit   = bytes[currentDataByteIndex];
                currentDataByteIndex++;
                state   = Bit7;
            }
            else
            {
                state   = StopCondition;
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
// Called at regular intervals to transmit an I2C bus protocol.
//
void ReadEngine()
{
    const uint8_t   numberOfStartStates     = 3;
    const uint8_t   numberOfStopStates      = 3;
    const uint8_t   numberOfBitsPerByte     = 8+1;                      // data+ACK.
    const uint8_t   numberOfStatesPerByte   = numberOfBitsPerByte*2;    // lo clock & hi clock.

    if(state == 0)
    {
        //
        // Start condition.
        //
        SET_SDA();
        SET_SCL();
    }
    else if(state == 1)
    {
        //
        // Start condition.
        //
        SET_SDA( false );
    }
    else if(state == 2)
    {
        //
        // Start condition.
        //
        CLEAR_SCL();
        SET_SDA();
    }
    else if( state < (numberOfBytesToTransfer*numberOfStatesPerByte)+numberOfStartStates )
    {
        uint8_t         byteIndex   = (state-3)/(2*9);
        static uint8_t  byte        = 0;
        uint8_t         bitInByte   = (state - ((byteIndex*numberOfStatesPerByte) + numberOfStartStates)) / 2;

        //
        // Reset the byte.
        //
        if(byteIndex == 0)
        {
            byte = 0;
        }

        //
        // Set the data/clock lines as appropriate.
        //
        if( (state%2) != 0)
        {
            CLEAR_SCL();        // bring clock down before setting new data.
        }
        else
        {
            SET_SCL();

            // TODO: Wait a bit to settle....

            if(bitInByte == 8)
            {
                if(I2CMasterByteReceived( byte ) == true)
                {
                    CLEAR_SDA();
                }
                else
                {
                    SET_SDA();
                }
            }
            else
            {
                bool bit = GET_SDA();
                if(bit == true)
                {
                    bit     |= (1<<bitInByte);
                }            
            }

        }
    }
    else
    {
        //Call( completionEvent );
        masterState     = Stopped;
    }

    state++;
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









#if 0

void I2CDisplay()
{

    if(masterState != Idle)
    {
        uint8_t*    sdaText;
        if(sda == true)
        {
            sdaText     = "|   ";
        }
        else
        {
            sdaText     = "   |";
        }
        if(sdaDriven == false)
        {
            sdaText     = "XXXX";
        }

        uint8_t*    sclText;
        if(scl == true)
        {
            sclText     = "|   ";
        }
        else
        {
            sclText     = "   |";
        }
    
        static bool sdaOld  = false;
        static bool sclOld  = false;
        if(sdaOld != sda)
        {
            sdaText     = "----";
        } 

        if(sclOld != scl)
        {
            sclText     = "----";
        } 

        //DPRINTF("%03d) %6s %6s \n",state, sclText, sdaText);
        sdaOld = sda;
        sclOld = scl;
    }    
}

#endif

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


