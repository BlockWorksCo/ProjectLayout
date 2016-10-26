//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "BoardSupport.h"
#include "ErrorHandling.h"







//
//
//
void EnableInterrupts()
{
}


//
//
//
void FlushCache()
{
}


//
//
//
void SetVectorTableAddress(uint32_t address)
{
}





uint32_t CoreNumber()
{
}




//
// Application entry point.
//
void __attribute__ ( ( naked ) ) EntryPoint()
{
    //
    // Call the CoreMain.
    //

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
#if 0
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
#endif
}





//
//
//
void BoardSupportInitialise()
{
    SetVectorTableAddress( (uint32_t)&VectorTable );
}




