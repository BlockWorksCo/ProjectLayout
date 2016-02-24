//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#include "TextFormatter.h"
#include <stdarg.h>


int vsnprintf(char *str, size_t len, const char *fmt, va_list ap);


//
//
//
void FormatTextFromVaList(char* output, uint32_t numberOfBytesInOutput, char* format, va_list vaList )
{
    memset( output, 0, numberOfBytesInOutput );
    vsnprintf( output, numberOfBytesInOutput, format, vaList );
}


//
//
//
void FormatText(char* output, uint32_t numberOfBytesInOutput, char* format, ...)
{
    static char     text[256];
    va_list         vaList;

    //
    // Form the text to store.
    //
    va_start(vaList, format);
    FormatTextFromVaList( output, sizeof(text), format, vaList );
    va_end(vaList);
}





