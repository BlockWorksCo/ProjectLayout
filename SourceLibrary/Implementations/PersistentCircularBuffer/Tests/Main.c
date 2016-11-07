



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
    // Write one record at the last position.
    //
    TestStruct testStructA  =
    {
        .fieldA     = true,
        .fieldB     = 0xab,
        .fieldC     = 0xfa,
    };
PersistentCircularBufferShowState(&pcbAContext);
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );
PersistentCircularBufferShowState(&pcbAContext);

    //
    // Overwrite with another record.
    //
    TestStruct testStructB  =
    {
        .fieldA     = false,
        .fieldB     = 0x80,
        .fieldC     = 0xfe,
    };
PersistentCircularBufferShowState(&pcbAContext);
    //PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructB );
    uint8_t     test[]  = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&test[0] );
    DebugHexDumpBytes( (uint8_t*)&testStructA, sizeof(testStructA) );
    DebugHexDumpBytes( (uint8_t*)&testStructB, sizeof(testStructB) );
    DebugHexDumpBytes( (uint8_t*)&test[0],     sizeof(testStructB) );

    //
    // Read the last record.
    //
    PersistentCircularBufferMoveToLast( &pcbAContext );
    //PersistentCircularBufferBack( &pcbAContext );
    TestStruct  readBackA   = {0};
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );
    DebugHexDumpBytes( (uint8_t*)&readBackA, sizeof(readBackA) );

    //
    // Check the record we read back.
    //
    AssertThat( readBackA.fieldA == false,  "fieldA is incorrect (%d)", readBackA.fieldA );
    AssertThat( readBackA.fieldB == 456,    "fieldB is incorrect.(%d)", readBackA.fieldB );
    AssertThat( readBackA.fieldC == 654,    "fieldC is incorrect.(%d)", readBackA.fieldC );
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


    testStructA.fieldB  = 0;
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );
    testStructA.fieldB  = 1;
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );
    testStructA.fieldB  = 2;
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );
    testStructA.fieldB  = 3;
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );

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
    AssertThat( readBackA.fieldB == 3,      "fieldB is incorrect." );
    AssertThat( readBackA.fieldC == 321,    "fieldC is incorrect." );

    //
    //
    //
    PersistentCircularBufferMoveToLast( &pcbAContext );
    PersistentCircularBufferBack( &pcbAContext );
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );

    AssertThat( readBackA.fieldA == true,   "fieldA is incorrect." );
    AssertThat( readBackA.fieldB == 2,      "fieldB is incorrect." );
    AssertThat( readBackA.fieldC == 321,    "fieldC is incorrect." );
}






//
//
//
int main()
{
#if 0
    uint32_t    a   = 2720;
    uint32_t    b   = 0x80000000;
    DebugPrintf("%08x %08x = %08x\n", a, b, (uint32_t)((uint64_t)b % (uint64_t)a) );
    //return;
#endif

    //
    //
    //
    FLASHDeviceInitialise();

    Reset();
    DebugPrintf("TestOne:\n");
    TestOne();

    Reset();
    DebugPrintf("TestTwo:\n");
    TestTwo();

    DebugPrintf("\nComplete.\n");
}


