



#include "Common.h"
#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"


bool        sdaData[128]    = {0};
bool        sclData[128]    = {0};
uint32_t    cycleCount      = 0;



bool I2CMasterByteReceived( uint8_t byte )
{
    return false;
}

void SET_SDA()
{
    //DebugPrintf("SET_SDA\n");
    sdaData[cycleCount] = true;
}

void CLEAR_SDA()
{
    //DebugPrintf("CLEAR_SDA\n");
    sdaData[cycleCount] = false;
}


void SET_SCL()
{
    //DebugPrintf("SET_SCL\n");
    sclData[cycleCount] = true;
}

void CLEAR_SCL()
{
    //DebugPrintf("CLEAR_SCL\n");
    sclData[cycleCount] = false;
}



bool GET_SDA()
{
    return true;
}



//
// Reset the test.
//
void Reset()
{
    cycleCount      = 0;
    ResetI2CMaster();

    cycleCount++;
    sdaData[cycleCount] = sdaData[cycleCount-1];
    sclData[cycleCount] = sclData[cycleCount-1];
}



//
// Single byte received with no idle time.
//
void TestOne()
{
    //
    // Setup for an I2C write of 4 bytes to address 0x52.
    //
    uint8_t     data[]  = {0x01,0x02,0x03,0x04};
    I2CWrite( 0x52, &data[0], sizeof(data) );

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<22; i++)
    {
        I2CMasterHandler();

        cycleCount++;
        sdaData[cycleCount] = sdaData[cycleCount-1];
        sclData[cycleCount] = sclData[cycleCount-1];
    }

    //
    // Show the data.
    //
    DebugPrintf("SCL: ");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c", (sclData[i]==true ? '-':'_') );
    }
    DebugPrintf("\n");

    DebugPrintf("SDA: ");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c", (sdaData[i]==true ? '-':'_') );
    }
    DebugPrintf("\n");

    //
    // Check the received data.
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


