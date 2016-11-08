



#include "Common.h"
#include "UARTReceiver.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"



PRIVATE bool*       rawData         = NULL;
PRIVATE uint32_t    sampleNumber   = 0;


//
//
//
bool GET_RX_STATE()
{
    bool    sample  = rawData[sampleNumber];
    sampleNumber++;

    return sample;
}


//
//
//
void Reset()
{
    //
    //
    //
    ResetUARTReceiver();
}



//
//
//
void TestOne()
{
    //
    // Set up the raw data.
    //
    bool    testData[]  = {0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 1,1,1,1};
    rawData         = &testData[0];
    sampleNumber    = 0;

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<(4*10); i++)
    {
        UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    uint8_t data    = GetUARTReceivedByte();
    AssertThat( data == 0x55,  "received byte is incorrect (%02x)", data );
}


//
//
//
void TestTwo()
{
    //AssertThat( txState == false,  "fieldA is incorrect (%d)", txState );
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


