//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Utilities.h"












void WriteEngine();
void ReadEngine();
void StopEngine();



typedef enum
{
    Transmitting,
    Receiving,
    Stopping,
    Idle,

} I2CMasterState;


#define    maxBytesToTransmit 64

I2CMasterState  masterState                         = Idle;
uint32_t        nextEdgeTime                        = 0;
bool            nextValue                           = 0;
I2CAddress      address                             = 0;
uint8_t         dataToTransmit[maxBytesToTransmit]  = {0};
uint8_t         acksForBytes[maxBytesToTransmit]    = {0};
uint8_t         numberOfBytesToTranfer              = 0;
uint8_t         state                               = 0;
bool            transferFinished                    = true;
uint8_t*        bytes                               = 0;
uint8_t         currentByteToTransmit               = 0;



//
//
//
void ResetI2CMaster()
{
    SET_SDA();
    SET_SCL();
}




//
//
//
void I2CWrite( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes )
{
    masterState         = Transmitting;
    state               = 0;

    address                 = _address;
    numberOfBytesToTranfer  = _numberOfBytes;
    bytes                   = _bytes;

    currentByteToTransmit   = address & (~0x1);
}


//
//
//
void I2CRead( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes )
{
    numberOfBytesToTranfer  = _numberOfBytes;
    masterState         = Receiving;
    state               = 0;
    address                 = _address;
}


//
//
//
void Stop()
{
    masterState         = Stopping;
    state               = 0;
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
        case 0:
        {
            CLEAR_SDA();    // Start condition.
            break;
        }

        case 1:
        {
            CLEAR_SCL();    // Start condition.
            break;
        }

        case 2:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 7) & 0x01 );    // b7
            SET_SCL();
            break;
        }

        case 3:
        {
            CLEAR_SCL();
            break;
        }

        case 4:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 6) & 0x01 );    // b6
            SET_SCL();
            break;
        }

        case 5:
        {
            CLEAR_SCL();
            break;
        }

        case 6:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 5) & 0x01 );    // b5
            SET_SCL();
            break;
        }

        case 7:
        {
            CLEAR_SCL();
            break;
        }

        case 8:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 4) & 0x01 );    // b4
            SET_SCL();
            break;
        }

        case 9:
        {
            CLEAR_SCL();
            break;
        }

        case 10:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 3) & 0x01 );    // b3
            SET_SCL();
            break;
        }

        case 11:
        {
            CLEAR_SCL();
            break;
        }

        case 12:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 2) & 0x01 );    // b2
            SET_SCL();
            break;
        }

        case 13:
        {
            CLEAR_SCL();
            break;
        }

        case 14:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 1) & 0x01 );    // b1
            SET_SCL();
            break;
        }

        case 15:
        {
            CLEAR_SCL();
            break;
        }

        case 16:
        {
            SetSDAAsPerData( (currentByteToTransmit >> 0) & 0x01 );    // b0
            SET_SCL();
            break;
        }

        case 17:
        {
            CLEAR_SCL();
            break;
        }

        case 18:
        {
            SET_SCL();      // ACK bit should be set by device now.
            break;
        }

        case 19:
        {
            CLEAR_SCL();
            SET_SDA();
            bool ackValue = GET_SDA(); // TODO: Get ACK bit.
            break;
        }

        case 20:
        {
            CLEAR_SDA();
            SET_SCL();                          // stop condition
            // TODO: Get ACK bit.
            break;
        }

        case 21:
        {
            SET_SDA();
            SET_SCL();                          // stop condition
            masterState     = Idle;
            break;
        }

        default:
        {
            PANIC();
            break;
        }
    }

    state++;
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
    else if( state < (numberOfBytesToTranfer*numberOfStatesPerByte)+numberOfStartStates )
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
        masterState     = Idle;
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
        masterState     = Idle;
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

        case Idle:
            break;

        default:
            PANIC();
            break;
    }

}


