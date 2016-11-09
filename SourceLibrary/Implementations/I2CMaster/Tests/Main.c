



#include "Common.h"
#include "I2CMaster.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"


bool*       sdaData         = 0;
uint32_t    sdaDataCount    = 0;
bool*       sclData         = 0;
uint32_t    sclDataCount    = 0;



bool I2CMasterByteReceived( uint8_t byte )
{
    return false;
}

void SET_SDA()
{
    //DebugPrintf("SET_SDA\n");
    sdaData[sdaDataCount] = true;
}

void CLEAR_SDA()
{
    //DebugPrintf("CLEAR_SDA\n");
    sdaData[sdaDataCount] = false;
}


void SET_SCL()
{
    //DebugPrintf("SET_SCL\n");
    sclData[sclDataCount] = true;
}

void CLEAR_SCL()
{
    //DebugPrintf("CLEAR_SCL\n");
    sclData[sclDataCount] = true;
}







void DRIVE_SDA()
{
    //DPRINTF("DRIVE_SDA\n");
    //sclData[sdaDataCount++] = true;
}

void FLOAT_SDA()
{
    //DPRINTF("FLOAT_SDA\n");
    //sdaDriven = false;
}

bool GET_SDA()
{
    //bool    sample  = rawData[sampleNumber];
    //sampleNumber++;

    //DebugPrintf("%d ", sample);

    //return sample;

    return true;
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
    //rawData         = &testData[0];
    //sampleNumber    = 0;

    //
    //
    //
    uint8_t     data[]  = {0x01,0x02,0x03,0x04};
    I2CWrite( 0xA5, &data[0], sizeof(data) );

    bool        testSDA[128]     = {0};     
    bool        testSCL[128]     = {0};
    sdaData         = &testSDA[0];     
    sclData         = &testSCL[0];
    sdaDataCount    = 0;
    sclDataCount    = 0;     

    //
    // Pump the data thru the receiver (8N1 format).
    //
    for(uint32_t i=0; i<20; i++)
    {
        I2CMasterHandler();
        sclDataCount++;
        sdaDataCount++;
    }

    //
    //
    //
    DebugPrintf("SCL: ");
    for(uint32_t i=0; i<sclDataCount; i++)
    {
        DebugPrintf("%c", (sclData[i]==true ? '-':'_') );
    }
    DebugPrintf("\n");

    DebugPrintf("SDA: ");
    for(uint32_t i=0; i<sdaDataCount; i++)
    {
        DebugPrintf("%c", (sdaData[i]==true ? '-':'_') );
    }
    DebugPrintf("\n");

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


