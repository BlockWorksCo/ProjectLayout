



#include <stdint.h>
#include <stdbool.h>
#include "UARTTransmitter.h"
#include "MemoryPool.h"
#include "FLASHDevice.h"
#include "PersistentCircularBuffer.h"



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
}


