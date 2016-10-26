//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "EventQueue.h"
#include "Utilities.h"




bool            sda                                 = false;
bool            sdaDriven                           = false;
bool            scl                                 = false;


void SET_SDA()
{
    //DPRINTF("SET_SDA\n");
    sda = true;
}

void CLEAR_SDA()
{
    //DPRINTF("CLEAR_SDA\n");
    sda = false;
}

void DRIVE_SDA()
{
    //DPRINTF("DRIVE_SDA\n");
    sdaDriven = true;
}

void FLOAT_SDA()
{
    //DPRINTF("FLOAT_SDA\n");
    sdaDriven = false;
}

bool GET_SDA()
{
    //DPRINTF("GET_SDA\n");
    return sda;
}

void SET_SCL()
{
    //DPRINTF("SET_SCL\n");
    scl = true;
}

void CLEAR_SCL()
{
    //DPRINTF("CLEAR_SCL\n");
    scl = false;
}













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
uint8_t         dataToTransmit[maxBytesToTransmit]  = {0};
uint8_t         acksForBytes[maxBytesToTransmit]    = {0};
uint8_t         numberOfBytesToTranfer              = 0;
uint8_t         state                               = 0;
bool            transferFinished                    = true;
Handler         completionEvent                     = 0;
uint8_t*        bytes                               = 0;
bool            (*byteReceivedCallback)(uint8_t);


//
//
//
void I2CWrite(uint8_t* _bytes, uint8_t _numberOfBytes, Handler _completionEvent )
{
    completionEvent     = _completionEvent;
    masterState         = Transmitting;
    state               = 0;

    numberOfBytesToTranfer  = _numberOfBytes;
    bytes                   = _bytes;
}

//
//
//
void I2CRead( bool (*_byteReceivedCallback)(uint8_t), uint8_t _numberOfBytes , Handler _completionEvent )
{
    numberOfBytesToTranfer  = _numberOfBytes;
    completionEvent     = _completionEvent;        
    masterState         = Receiving;
    state               = 0;

    byteReceivedCallback = _byteReceivedCallback;
}

//
//
//
void Stop( Handler _completionEvent )
{
    completionEvent     = _completionEvent;        
    masterState         = Stopping;
    state               = 0;
}















//
// Called at regular intervals to transmit an I2C bus protocol.
//
void WriteEngine()
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
        DRIVE_SDA();
        SET_SDA();
        SET_SCL();
    }
    else if(state == 1)
    {
        //
        // Start condition.
        //
        CLEAR_SDA();
    }
    else if(state == 2)
    {
        //
        // Start condition.
        //
        SET_SCL();
    }
    else if( state < (numberOfBytesToTranfer*numberOfStatesPerByte)+numberOfStartStates )
    {
        uint8_t             byteIndex   = (state-3)/(2*9);
        uint8_t             byte        = bytes[ byteIndex ];
        volatile uint8_t    bitInByte   = (state - ((byteIndex*numberOfStatesPerByte) + numberOfStartStates)) / 2;

        //
        // Set the data/clock lines as appropriate.
        //
        if( (state%2) != 0)
        {
            CLEAR_SCL();        // bring clock down before setting new data.
            if(bitInByte == 8)
            {
                FLOAT_SDA();
            }
            else
            {
                DRIVE_SDA();

                volatile uint8_t bitValue = byte&(0x80>>bitInByte);
//DPRINTF("                        bn=%d byte=%02x\n",bitInByte,byte);                
                if( bitValue != 0 )
                {
                    SET_SDA();
                }
                else
                {
                    CLEAR_SDA();
                }

            }
        }
        else
        {
            SET_SCL();

            if(bitInByte == 8)
            {
                acksForBytes[byteIndex] = GET_SDA();         // detect ACK.                                
            }
        }
    }
    else
    {
        Call( completionEvent );
        masterState     = Idle;
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
        DRIVE_SDA();
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
        FLOAT_SDA();
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
            FLOAT_SDA();

            // TODO: Wait a bit to settle....

            if(bitInByte == 8)
            {
                DRIVE_SDA();
                if(byteReceivedCallback( byte ) == true)
                {
                    CLEAR_SDA();
                }
                else
                {
                    DRIVE_SDA();
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
        Call( completionEvent );
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
        DRIVE_SDA();
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

        Call( completionEvent );
        masterState     = Idle;
    }

    state++;
}











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



//
//
//
void i2cISR()
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


