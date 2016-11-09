



#include "Common.h"
#include "UARTReceiver.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"



PRIVATE bool*       rawData         = NULL;
PRIVATE uint32_t    sampleNumber   = 0;


//
// Return the sample data.
//
bool GET_RX_STATE()
{
    bool    sample  = rawData[sampleNumber];
    sampleNumber++;

    DebugPrintf("%d ", sample);

    return sample;
}


//
// Reset the test.
//
void Reset()
{
    ResetUARTReceiver();
}



//
// Single byte received with no idle time.
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
// one byte received with leading idle time.
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
// Two bytes received with leading idle time for byte 1 and no gap to byte 2.
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
// two bytes received with leading idle time 14 & 17 clocks.
//
void TestFour()
{
    //
    // Set up the raw data.
    //
    bool    testData[]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1,   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1 };
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
    for(uint32_t i=0; i<17+40; i++)
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
// Entry point.
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

    Reset();
    DebugPrintf("TestFour:\n");
    TestFour();

    DebugPrintf("\nComplete.\n");
}


