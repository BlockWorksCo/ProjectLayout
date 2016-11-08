//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "UARTReceiver.h"
#include "ErrorHandling.h"


PRIVATE bool    rxState             = false;
PRIVATE bool    rxDriven            = false;
PRIVATE uint8_t state               = 0;
PRIVATE uint8_t byteBeingReceived   = 0x00;


void SET_RX()
{
    rxState  = true;
}

void CLEAR_RX()
{
    rxState = false;
}

void FLOAT_RX()
{
    rxDriven    = false;
}

void DRIVE_RX()
{
    rxDriven = true;
}




void UARTReceiveHandler()
{
    if( state == 0 )
    {
        //
        // Start bit.
        //
        FLOAT_RX();
        //CLEAR_TX();
    }
    else if( (state>=1) && (state<9) )
    {
        uint8_t     bitNumber = state-1;

        //
        // data bits
        //
        if( (byteBeingReceived&(1<<bitNumber)) != 0)
        {
            //SET_TX();
        }
        else
        {
            //CLEAR_TX();
        }
    }
    else if( state == 9 )
    {
        //
        // Stop bit.
        //
        //SET_TX();
    }

    state++;    
}



uint8_t GetUARTReceivedByte()
{
    state = 0;
    while(state <= 9)
    {
        UARTReceiveHandler();
    }

    return 0;
}



