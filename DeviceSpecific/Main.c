



#include <stdint.h>
#include <stdbool.h>
#include "MemoryPool.h"
#include "FLASHDevice.h"
#include "PersistentCircularBuffer.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DataTable.h"



typedef struct
{
    bool        fieldA;
    uint32_t    fieldB;
    uint64_t    fieldC;

} TestStruct;



//
//
//
void main()
{
    //
    //
    //
    FLASHDeviceInitialise();

    //
    //
    //
    PersistentCircularBufferContext     pcbAContext;
    PersistentCircularBufferLayout      pcbALayout      = LAYOUT( 0,16, sizeof(TestStruct) );
    PersistentCircularBufferInitialise( &pcbAContext, &pcbALayout );

    //
    //
    //
    TestStruct testStructA  =
    {
        .fieldA     = true,
        .fieldB     = 123,
        .fieldC     = 321,
    };
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructA );

    TestStruct testStructB  =
    {
        .fieldA     = false,
        .fieldB     = 456,
        .fieldC     = 654,
    };
    PersistentCircularBufferUpdateLast( &pcbAContext, (uint8_t*)&testStructB );

    PersistentCircularBufferMoveToLast( &pcbAContext );
    TestStruct  readBackA   = {0};
    PersistentCircularBufferPeek( &pcbAContext, (uint8_t*)&readBackA );

    //AssertThat( readBackA.fieldA == false );
    //AssertThat( readBackA.fieldB == 456 );
    //AssertThat( readBackA.fieldB == 654 );

    PersistentCircularBufferShowState( &pcbAContext );
}


