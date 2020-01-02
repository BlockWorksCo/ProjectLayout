//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, January 2020.
//


#include "BoardSupport.h"
#include "ErrorHandling.h"
#include "stm32f10x.h"





uint32_t    sysTickCount    = 0;

void SysTick_Handler()
{
    sysTickCount++;
}


//
//
//
uint32_t GetTickCount()
{
    return sysTickCount;
}

//
//
//
uint32_t CurrentTimestamp_ms()
{
    return sysTickCount;
}




//
//
//
void Delay_ms(uint32_t ms)
{
    uint32_t    start   = CurrentTimestamp_ms();
    while(CurrentTimestamp_ms() < (start+ms) );
}


//
//
//
void Delay_us(uint32_t us)
{
    // minimum delay of 1ms.
    Delay_ms(1);
}


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
    return (uint32_t)0;
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

    //SysTick_Config(SystemCoreClock/100);
    SysTick_Config(50000);
}




