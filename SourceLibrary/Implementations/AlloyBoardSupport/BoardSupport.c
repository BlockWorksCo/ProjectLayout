//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "BoardSupport.h"
#include "ErrorHandling.h"
#include "Alloy.h"



#define STACK_SIZE              (1024)
#define NUMBER_OF_ALLOY_CORES   (4)
#define NUMBER_OF_VECTORS       (256)



//
//
//
void CoreMain(uint32_t coreID);




//
//
//
uint8_t     usrStack[NUMBER_OF_ALLOY_CORES*STACK_SIZE];
uint8_t     irqStack[NUMBER_OF_ALLOY_CORES*STACK_SIZE];


GlobalData              globals[NUMBER_OF_CORES];
CoreServicesBridge*     bridge                      = (CoreServicesBridge*)BRIDGE_BASE;




//
//
//
void BoardSupportInitialise()
{

}








//
// Get the Multiprocessor affinity register (core id).
//
uint32_t MPIDR()
{
    uint32_t    mpidr;

    __asm__ volatile("mrc p15, 0, %0, c0, c0, 5\n\t" : "=r"(mpidr));    

    uint32_t coreID     = mpidr & 0x03;
    return coreID;
}


uint32_t CoreNumber()
{
    return MPIDR();
}



//
//
//
GlobalData* Globals()
{
    uint32_t    coreID              = MPIDR();

    return &globals[coreID];
}




//
// Application entry point.
//
void __attribute__ ( ( naked ) ) EntryPoint()
{
    //
    // Setup the stack(s).
    //
    uint32_t   mpidr;

    //
    //
    //
    __asm__ volatile("mrc p15, 0, %0, c0, c0, 5\n\t" : "=r"(mpidr) ); 
    uint32_t    coreID  = mpidr&0x3;   

    //
    //
    //
    uint32_t            usrStackPointer    = ((uint32_t)&usrStack[coreID*STACK_SIZE]) + STACK_SIZE - 16;
    __asm__ volatile("MOV sp, %0\n\t" : : "r"(usrStackPointer));

    //
    //
    //
    uint32_t            irqStackPointer    = ((uint32_t)&irqStack[coreID*STACK_SIZE]) + STACK_SIZE - 16;
    __asm__ volatile("MSR     CPSR_c, 0xd2");
    __asm__ volatile("MOV sp, %0\n\t" : : "r"(irqStackPointer));
    __asm__ volatile("MSR     CPSR_c, 0xd3");

    //
    //
    //
    Globals()->numberOfMessagesAvailable   = 0;
    bridge                      = (CoreServicesBridge*)BRIDGE_BASE;    

    //
    // Call the CoreMain.
    //
    CoreMain(coreID);

    //
    // Should never get here.
    //
    PANIC();
}



