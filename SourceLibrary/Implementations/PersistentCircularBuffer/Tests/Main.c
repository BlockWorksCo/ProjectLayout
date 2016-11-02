



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
        .fieldB     = 123,
        .fieldC     = 321,
    };
    PersistentCircularBufferAdd( &pcbAContext, (uint8_t*)&testStructA );

    //
    // Overwrite with another record.
    //
    TestStruct testStructB  =
    {
        .fieldA     = false,
        .fieldB     = 456,
        .fieldC     = 654,
    };
PersistentCircularBufferShowState(&pcbAContext);
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructB );
PersistentCircularBufferShowState(&pcbAContext);

    //
    // Read the last record.
    //
    PersistentCircularBufferMoveToLast( &pcbAContext );
    //PersistentCircularBufferBack( &pcbAContext );
    TestStruct  readBackA   = {0};
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );

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


