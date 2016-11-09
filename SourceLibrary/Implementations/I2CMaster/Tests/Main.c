



#include "Common.h"
#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"



PRIVATE bool*       rawData         = NULL;
PRIVATE uint32_t    sampleNumber   = 0;



bool            sda                                 = false;
bool            sdaDriven                           = false;
bool            scl                                 = false;




bool I2CMasterByteReceived( uint8_t byte )
{

}

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
    bool    sample  = rawData[sampleNumber];
    sampleNumber++;

    DebugPrintf("%d ", sample);

    return sample;
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



//
// Reset the test.
//
void Reset()
{
    ResetI2CMaster();
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
    //rawData         = &testData[0];
    //sampleNumber    = 0;

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(testData); i++)
    {
        //UARTReceiveHandler();
    }

    //
    // Check the received byte.
    //
    //AssertThat( data == 0xaa,  "received byte is incorrect (%02x)", data );
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

    DebugPrintf("\nComplete.\n");
}


