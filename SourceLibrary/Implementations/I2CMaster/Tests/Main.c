



#include "Common.h"
#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"


bool        sdaData[128]        = {0};
bool        sclData[128]        = {0};
bool        slaveSDAData[128]   = {0};
bool        slaveSCLData[128]   = {0};
bool        sclSetState         = true;
bool        sdaSetState         = true;
uint32_t    cycleCount          = 0;
bool        restartRead         = false;

bool I2CMasterByteReceived( uint8_t byte )
{
    return false;
}

void SET_SDA()
{
    // Change to input, allowing pull-up to raise the level (open drain).
    sdaSetState         = true;
    sdaData[cycleCount] = sdaSetState & slaveSDAData[cycleCount];  // wired-AND
}

void CLEAR_SDA()
{
    // Change to output, driving down to ground (open drain).
    sdaSetState         = false;
    sdaData[cycleCount] = sdaSetState & slaveSDAData[cycleCount];  // wired-AND
}


void SET_SCL()
{
    // Change to input, allowing pull-up to raise the level (open drain).
    sclSetState         = true;
    sclData[cycleCount] = sclSetState & slaveSCLData[cycleCount];  // wired-AND
}

void CLEAR_SCL()
{
    // Change to output, driving down to ground (open drain).
    sclSetState         = false;
    sclData[cycleCount] = sclSetState & slaveSCLData[cycleCount];  // wired-AND
}



bool GET_SDA()
{
    // Change to input, allowing pull-up to raise the level or other device to drive it down (open drain).
    sdaData[cycleCount]     = slaveSDAData[cycleCount] & sdaSetState;   // wired-AND
    return sdaData[cycleCount];
}

bool GET_SCL()
{
    // Change to input, allowing pull-up to raise the level or other device to drive it down (open drain).
    sclData[cycleCount]     = slaveSCLData[cycleCount] & sclSetState;   // wired-AND
    return slaveSCLData[cycleCount];
}


void I2C_BYTE_RECEIVED(uint8_t byte)
{
    DebugPrintf("<rx: %02x>\n", byte);
}


void I2C_OPERATION_COMPLETE()
{
    DebugPrintf("<Operation complete>\n");

    if(restartRead == true)
    {
        static uint8_t     data[]          = {0x00};
        I2CRead( 0x52, &data[0], sizeof(data) );
    }
}



//
// Reset the test.
//
void Reset()
{
    cycleCount              = 0;
    restartRead             = false;

    memset( &slaveSCLData[0], 1,            sizeof(slaveSCLData) );
    memset( &slaveSDAData[0], 1,            sizeof(slaveSDAData) );
    sdaSetState         = true;
    sclSetState         = true;

    ResetI2CMaster();

    cycleCount++;
    SET_SDA();
    SET_SCL();
}



//
// 4 bytes output from master.
//
void TestOne()
{
    //
    // Setup for an I2C write of 4 bytes to address 0x52.
    //
    uint8_t     data[]  = {0x00,0x01,0x02,0x03};
    bool        slaveSDA[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0 ,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1
,1,1,1,1,1,1,1,1,1,1,1,1,1,};
    memcpy( &slaveSDAData[0], &slaveSDA[0], sizeof(slaveSDAData) );
    memset( &slaveSCLData[0], 1,            sizeof(slaveSCLData) );

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
    DebugPrintf("     ");
    for(uint32_t i=0; i<cycleCount/2; i++)
    {
        DebugPrintf("%d ", i%9 );
    }
    DebugPrintf("\n");

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
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0
,0,0,0,0,0,1,1,1,1,1,1,0,1,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}






//
// 4 bytes read from slave.
//
void TestTwo()
{
    //
    // Setup for an I2C read of 4 bytes to address 0x52.
    //
    uint8_t     data[]          = {0x00,0x01,0x02,0x03}; //                        A A                     1 1                               1 1                         1 1                             1 1
    bool        slaveSDA[]      = {1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 0,0, 1,1, 1,1, 0,0, 0,0, 0,0, 0,0, 1,1, 1,1, 0,0, 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0, 0 ,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0, 0, 0,0,0,1,1,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    memcpy( &slaveSDAData[0], &slaveSDA[0], sizeof(slaveSDAData) );
    memset( &slaveSCLData[0], 1,            sizeof(slaveSCLData) );

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
    DebugPrintf("     ");
    for(uint32_t i=0; i<cycleCount/2; i++)
    {
        DebugPrintf("%d ", i%9 );
    }
    DebugPrintf("\n");

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
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}



//
// 4 bytes read from slave with NAK after two.
//
void TestThree()
{
    //
    // Setup for an I2C read of 4 bytes to address 0x52.
    //
    uint8_t     data[]          = {0x00,0x01,0x02,0x03};
    bool        slaveSDA[]      = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0, 0, 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0, 1 ,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0, 0, 0,0,0,1,1,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    memcpy( &slaveSDAData[0], &slaveSDA[0], sizeof(slaveSDAData) );
    memset( &slaveSCLData[0], 1,            sizeof(slaveSCLData) );

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
    DebugPrintf("     ");
    for(uint32_t i=0; i<cycleCount/2; i++)
    {
        DebugPrintf("%d ", i%9 );
    }
    DebugPrintf("\n");

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
    bool    goodSCLData[]   = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
,1,1,1,1,1,1,1,1,1,1,1,1,1,};
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}




//
// 2 bytes read from slave clock stretching by slave.
//
void TestFour()
{
    //
    // Setup for an I2C read of 4 bytes to address 0x52.
    //
    uint8_t     data[]          = {0x00,0x01,0x02,0x03}; //                        A A                     1 1                               1 1                         1 1                             1 1
    bool        slaveSDA[]      = {1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 0,0, 1,1,1,1,1,1,  1,1, 1,1, 0,0, 0,0, 0,0, 0,0, 1,1, 1,1, 0,0, 0,0, 0,0,0,0,0,0,0,0,0,1,1,0,0,0,0, 1,1, 0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0, 0, 0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    bool        slaveSCL[]      = {1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 0,0,0,0,0,0,  1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1, 1 ,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};

    memcpy( &slaveSDAData[0], &slaveSDA[0], sizeof(slaveSDAData) );
    memcpy( &slaveSCLData[0], &slaveSCL[0], sizeof(slaveSCLData) );

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
    DebugPrintf("     ");
    for(uint32_t i=0; i<cycleCount/2; i++)
    {
        DebugPrintf("%d ", i%9 );
    }
    DebugPrintf("\n");

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
    bool    goodSCLData[]   = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
,1,1,1,1,1,1,1,1,1,1,1,1,1,};
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}


//
// 2 bytes written to slave then 2 bytes received from slave with repeated start.
//
void TestFive()
{
    //
    // Setup for an I2C write of 4 bytes to address 0x52.
    //
    uint8_t     data[]  = {0x00,0x01};
    bool        slaveSDA[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0, 0, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0 ,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0, 0, 1,1,1,1,1,1,1
,1,1,1,1,1,1,1,1,1,1,1,1,1,};
    memcpy( &slaveSDAData[0], &slaveSDA[0], sizeof(slaveSDAData) );
    memset( &slaveSCLData[0], 1,            sizeof(slaveSCLData) );

    I2CWrite( 0x52, &data[0], sizeof(data) );
    restartRead     = true;

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
    DebugPrintf("     ");
    for(uint32_t i=0; i<cycleCount/2; i++)
    {
        DebugPrintf("%d ", i%9 );
    }
    DebugPrintf("\n");

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
    bool    goodSDAData[]   = {1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0
,0,0,0,0,0,1,1,1,1,1,1,0,1,};
    AssertThat( cycleCount == NUMBER_OF_ELEMENTS(goodSCLData),              "cycle count is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSCLData[0], &sclData[0], cycleCount) == 0,      "SCL data is incorrect (%d)", cycleCount );
    AssertThat( memcmp(&goodSDAData[0], &sdaData[0], cycleCount) == 0,      "SDA data is incorrect (%d)", cycleCount );
}


//
// 2 bytes written to nonexistant slave.
//
void TestSix()
{
}

//
// 2 bytes read from nonexistant slave.
//
void TestSeven()
{
}

//
// 2 bytes read from slave then 2 bytes transmitted to slave with repeated start.
//
void TestEight()
{
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

    Reset();
    DebugPrintf("TestFive:\n");
    TestFive();

    Reset();
    DebugPrintf("TestSix:\n");
    TestSix();

    Reset();
    DebugPrintf("TestSeven:\n");
    TestSeven();

    Reset();
    DebugPrintf("TestEight:\n");
    TestEight();

    DebugPrintf("\nComplete.\n");
}


