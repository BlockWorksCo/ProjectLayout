



#include "Common.h"
#include "UARTTransmitter.h"
#include "ErrorHandling.h"
#include "Assertions.h"
#include "DebugText.h"



bool    txState = false;

void SET_TX()
{
    txState  = true;
}

void CLEAR_TX()
{
    txState = false;
}





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
    //
    // Check the record we read back.
    //
    AssertThat( txState == false,  "fieldA is incorrect (%d)", txState );
}


//
//
//
void TestTwo()
{
    AssertThat( txState == false,  "fieldA is incorrect (%d)", txState );
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


