



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

    DebugPrintf("%d ", sample);

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
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(testData); i++)
    {
        UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    uint8_t data    = GetUARTReceivedByte();
    AssertThat( data == 0xaa,  "received byte is incorrect (%02x)", data );
}


//
//
//
void TestTwo()
{
    //
    // Set up the raw data.
    //
    bool    testData[]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1};
    rawData         = &testData[0];
    sampleNumber    = 0;

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(testData); i++)
    {
        UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    uint8_t data    = GetUARTReceivedByte();
    AssertThat( data == 0x03,  "received byte is incorrect (%02x)", data );
}




//
//
//
void TestThree()
{
    //
    // Set up the raw data.
    //
    bool    testData[]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1 };
    rawData         = &testData[0];
    sampleNumber    = 0;

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<14+40; i++)
    {
        UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    uint8_t data0   = GetUARTReceivedByte();
    AssertThat( data0 == 0x03,  "received byte is incorrect (%02x)", data0 );

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<40; i++)
    {
        UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    uint8_t data1   = GetUARTReceivedByte();
    AssertThat( data1 == 0x06,  "received byte is incorrect (%02x)", data1 );
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

    Reset();
    DebugPrintf("TestThree:\n");
    TestThree();

    DebugPrintf("\nComplete.\n");
}


