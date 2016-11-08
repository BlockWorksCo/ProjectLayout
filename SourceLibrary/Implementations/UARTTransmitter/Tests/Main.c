



#include "Common.h"
#include "UARTTransmitter.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"



bool    txState = false;

void SET_TX()
{
    txState  = true;
}

void CLEAR_TX()
{
    txState = false;
}





//
//
//
void Reset()
{
    //
    //
    //
    ResetUARTTransmitter();
}



//
//
//
void TestOne()
{
    AssertThat( txState == true,   "Idle state incorrect" );

    //
    // Check the record we read back.
    //
    UARTTransmitByte( 0x55 );

    //
    //
    //
    UARTTransmitHandler();
    AssertThat( txState == false,   "Start state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Bit0 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == false,  "Bit1 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Bit2 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == false,  "Bit3 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Bit4 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == false,  "Bit5 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Bit6 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == false,  "Bit7 state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Stop state incorrect" );

    UARTTransmitHandler();
    AssertThat( txState == true,   "Idle state incorrect" );
}


//
//
//
void TestTwo()
{
    AssertThat( txState == false,  "fieldA is incorrect (%d)", txState );
}






//
//
//
int main()
{
    //
    //
    //
    Reset();
    DebugPrintf("TestOne:\n");
    TestOne();

    Reset();
    DebugPrintf("TestTwo:\n");
    TestTwo();

    DebugPrintf("\nComplete.\n");
}


