



#include "Common.h"
#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"


bool        sdaData[128]        = {0};
bool        sclData[128]        = {0};
bool        slaveSDAData[128]   = {0};
uint32_t    cycleCount          = 0;


bool I2CMasterByteReceived( uint8_t byte )
{
    return false;
}

void SET_SDA()
{
    // Change to input, allowing pull-up to raise the level (open drain).
    sdaData[cycleCount] = true;
}

void CLEAR_SDA()
{
    // Change to output, driving down to ground (open drain).
    sdaData[cycleCount] = false;
}


void SET_SCL()
{
    // Change to input, allowing pull-up to raise the level (open drain).
    sclData[cycleCount] = true;
}

void CLEAR_SCL()
{
    // Change to output, driving down to ground (open drain).
    sclData[cycleCount] = false;
}



bool GET_SDA()
{
    // Change to input, allowing pull-up to raise the level or other device to drive it down (open drain).
    return slaveSDAData[cycleCount];
}



//
// Reset the test.
//
void Reset()
{
    cycleCount              = 0;
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
    uint8_t     data[]  = {0x00,0x01,0x02,0x03};
    bool        slaveResponse[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    memcpy( &slaveSDAData[0], &slaveResponse[0], sizeof(slaveResponse) );
    I2CWrite( 0x52, &data[0], sizeof(data) );

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<2*(1+9*5+1); i++)
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
#if 0
    DebugPrintf("scl={");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c,", (sclData[i]==true ? '1':'0') );
    }
    DebugPrintf("}\n");

    DebugPrintf("sda={");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c,", (sdaData[i]==true ? '1':'0') );
    }
    DebugPrintf("}\n");
#endif
    //
    // Check the received data.
    //                         I S   0   1   2   3   4   5   6   7   A   S I
    bool    goodSCLData[]   = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1
,0,1,0,1,0,1,0,1,0,1,0,1,1,};
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0
,0,0,0,0,0,1,1,1,1,1,1,0,1,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}






//
// Single byte received with no idle time.
//
void TestTwo()
{
    //
    // Setup for an I2C read of 4 bytes to address 0x52.
    //
    uint8_t     data[]          = {0x00,0x01,0x02,0x03};
    bool        slaveResponse[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1, 0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    memcpy( &slaveSDAData[0], &slaveResponse[0], sizeof(slaveResponse) );

    I2CRead( 0x52, &data[0], sizeof(data) );

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<2*(1+9*5+1); i++)
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
#if 0
    DebugPrintf("scl={");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c,", (sclData[i]==true ? '1':'0') );
    }
    DebugPrintf("}\n");

    DebugPrintf("sda={");
    for(uint32_t i=0; i<cycleCount; i++)
    {
        DebugPrintf("%c,", (sdaData[i]==true ? '1':'0') );
    }
    DebugPrintf("}\n");
#endif
    //
    // Check the received data.
    //                         I S   0   1   2   3   4   5   6   7   A   S I
    bool    goodSCLData[]   = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1
,0,1,0,1,0,1,0,1,0,1,0,1,1,};
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0
,0,0,0,0,0,1,1,1,1,1,1,0,1,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
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

    DebugPrintf("\nComplete.\n");
}


