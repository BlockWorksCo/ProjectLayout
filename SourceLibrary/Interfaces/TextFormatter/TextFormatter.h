//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#ifndef __TEXTFORMATTER_H_
#define __TEXTFORMATTER_H_


#include "Common.h"

void FormatTextFromVaList(char* output, uint32_t numberOfBytesInOutput, char* format, va_list vaList );
void FormatText(char* output, uint32_t numberOfBytesInOutput, char* format, ...);



#endif



