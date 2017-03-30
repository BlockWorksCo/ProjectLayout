//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#ifndef __MESSAGEBOX_H__
#define __MESSAGEBOX_H__



#include <stdint.h>
#include <stdbool.h>




void MessageBoxInitialise(void);
bool MessageBoxRead(uint32_t queueId, uint32_t* value);
bool MessageBoxWrite(uint32_t queueId, uint32_t value);

#endif



