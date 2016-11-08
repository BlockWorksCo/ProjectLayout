



#include "Common.h"
#include "UARTReceiver.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"




//
//
//
void Reset()
{
    //
    //
    //
}



//
//
//
void TestOne()
{
    UARTReceiveHandler();

    uint8_t data    = GetUARTReceivedByte();
    AssertThat( data == 0x00,  "received byte is incorrect (%d)", data );
}


//
//
//
void TestTwo()
{
    //AssertThat( txState == false,  "fieldA is incorrect (%d)", txState );
}






//
//
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


