//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __BOARDSUPPORT_H__
#define __BOARDSUPPORT_H__



#include "Common.h"





uint32_t CoreNumber();
void BoardSupportInitialise();
void EnableInterrupts();
void TriggerMailboxInterrupt(uint32_t toID);
void FlushCache();
uint32_t GetTickCount();
uint32_t CurrentTimestamp_ms();
void Delay_ms(uint32_t ms);
void Delay_us(uint32_t us);

#endif


