//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "BoardSupport.h"
#include "ErrorHandling.h"
#include "Alloy.h"
#include "ThreadLocalStorage.h"



#define STACK_SIZE              (1024)
#define NUMBER_OF_ALLOY_CORES   (4)
#define NUMBER_OF_VECTORS       (256)



#define dsb(option) asm volatile ("dsb " #option : : : "memory")
#define EI()        asm volatile ("cpsie i")
#define DI()        asm volatile ("cpsid i")



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
// Cause a reset request.
//
void CWRR()
{
    //
    // Cause a reset request.
    //
    register uint32_t    cwrr    = 0x00000002;
    __asm__ volatile("mcr p14, 0, %0, c1, c4, 4\n\t" : : "r"(cwrr));
}



//
//
//
void EnableInterrupts()
{
    EI();
}


//
//
//
void FlushCache()
{
    dsb();
}

//
//
//
void TriggerMailboxInterrupt(uint32_t toID)
{
    uint32_t    mailboxSetAddress;
    uint32_t    coreID  = CoreNumber();

    mailboxSetAddress     = 0x40000080 + (0x10*toID);
    *(uint32_t*)mailboxSetAddress     = 1<<coreID;

    FlushCache();
}


//
//
//
void SetVectorTableAddress(uint32_t address)
{
    register uint32_t   temp    = address;
    asm volatile ("mcr p15, 0, %0, c12, c0,  0" : "=r" (temp));
}





//
//
//
void  __attribute__ ((interrupt ("IRQ"))) Handler()
{
    PANIC();
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






//
//
//
void __attribute__ ( (naked, aligned(128) ) ) VectorTable()
{
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =IRQHandler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
    asm volatile ("ldr pc, =Handler");
}





//
//
//
void BoardSupportInitialise()
{
    SetVectorTableAddress( (uint32_t)&VectorTable );
}




