//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "Common.h"
#include "UARTTransmitter.h"
#include "ErrorHandling.h"



//
//
//
typedef enum
{
    Idle,
    Start,
    Bit0,
    Bit1,
    Bit2,
    Bit3,
    Bit4,
    Bit5,
    Bit6,
    Bit7,
    Parity,
    Stop,

} UARTTransmitterState;


PRIVATE uint8_t                 byteToTransmit  = 0;
PRIVATE UARTTransmitterState    state           = Idle;
PRIVATE bool                    parityValue     = 0;



//
//
//
void ResetUARTTransmitter()
{
    state   = Idle;
    SET_TX();
}


//
//
//
void SetBitValue( uint8_t bitValue )
{
    if( bitValue != 0 )
    {
        SET_TX();
    }
    else
    {
        CLEAR_TX();
    }
}


//
//
//
void UARTTransmitHandler()
{
    switch(state)
    {
        case Idle:
        {
            SET_TX();
            break;
        }

        case Start:
        {
            CLEAR_TX();
            state   = Bit0;
            break;
        }

        case Bit0:
        {
            SetBitValue( byteToTransmit & 0x01 );
            state   = Bit1;
            break;
        }

        case Bit1:
        {
            SetBitValue( byteToTransmit & 0x02 );
            state   = Bit2;
            break;
        }

        case Bit2:
        {
            SetBitValue( byteToTransmit & 0x04 );
            state   = Bit3;
            break;
        }

        case Bit3:
        {
            SetBitValue( byteToTransmit & 0x08 );
            state   = Bit4;
            break;
        }

        case Bit4:
        {
            SetBitValue( byteToTransmit & 0x10 );
            state   = Bit5;
            break;
        }

        case Bit5:
        {
            SetBitValue( byteToTransmit & 0x20 );
            state   = Bit6;
            break;
        }

        case Bit6:
        {
            SetBitValue( byteToTransmit & 0x40 );
            state   = Bit7;
            break;
        }

        case Bit7:
        {
            SetBitValue( byteToTransmit & 0x80 );
            state   = Stop;
            break;
        }

        case Parity:
        {
            state   = Idle;
            SetBitValue( parityValue );
            break;
        }

        case Stop:
        {
            SET_TX();
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
//
//
void UARTTransmitByte( uint8_t byte )
{
    if( state == Idle )
    {
        ResetUARTTransmitter();

        state           = Start;
        byteToTransmit  = byte;
        parityValue     = 0;
    }
}
        



