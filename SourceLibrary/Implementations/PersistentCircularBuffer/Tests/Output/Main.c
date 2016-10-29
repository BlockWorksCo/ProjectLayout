



#include <stdint.h>
#include <stdbool.h>
#include "FLASHDevice.h"
#include "PersistentCircularBuffer.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"


typedef struct
{
    bool        fieldA;
    uint32_t    fieldB;
    uint64_t    fieldC;

} TestStruct;


PersistentCircularBufferContext     pcbAContext;
PersistentCircularBufferLayout      pcbALayout      = LAYOUT( 0,16, sizeof(TestStruct) );


//
//
//
void Reset()
{
    //
    //
    //
    PersistentCircularBufferInitialise( &pcbAContext, &pcbALayout );
    PersistentCircularBufferEraseAll( &pcbAContext );
}



//
//
//
void TestOne()
{
    //
    // Write one record.
    //
    TestStruct testStructA  =
    {
        .fieldA     = true,
        .fieldB     = 123,
        .fieldC     = 321,
    };
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );

    //
    // Write another record.
    //
    TestStruct testStructB  =
    {
        .fieldA     = false,
        .fieldB     = 456,
        .fieldC     = 654,
    };
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructB );

    //
    // Read the last record.
    //
    PersistentCircularBufferMoveToLast( &pcbAContext );
    TestStruct  readBackA   = {0};
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );

    //
    // Check the record we read back.
    //
    AssertThat( readBackA.fieldA == false,  "fieldA is incorrect." );
    AssertThat( readBackA.fieldB == 456,    "fieldB is incorrect." );
    AssertThat( readBackA.fieldC == 654,    "fieldC is incorrect." );
}


//
//
//
void TestTwo()
{
    //
    // Write 16 records.
    //
    TestStruct testStructA  =
    {
        .fieldA     = true,
        .fieldB     = 0,
        .fieldC     = 321,
    };

    for(uint32_t i=0; i<16; i++)
    {
        PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );
        testStructA.fieldB++;
    }

    //
    // Read the last record.
    //
    PersistentCircularBufferMoveToLast( &pcbAContext );
    TestStruct  readBackA   = {0};
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );

    //
    // Check the record we read back.
    //
    AssertThat( readBackA.fieldA == true,   "fieldA is incorrect." );
    AssertThat( readBackA.fieldB == 15,     "fieldB is incorrect." );
    AssertThat( readBackA.fieldC == 31,    "fieldC is incorrect." );
}






//
//
//
void main()
{
    DebugPrintf("\nTests starting.\n");

    //
    //
    //
    FLASHDeviceInitialise();

    Reset();
    TestOne();

    Reset();
    TestTwo();

    DebugPrintf("\nComplete.\n");
}


