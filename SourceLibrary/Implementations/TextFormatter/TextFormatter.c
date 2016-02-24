//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#include "TextFormatter.h"
#include <stdarg.h>

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
    memset(&text[0], 0, sizeof(text));
    //vsprintf(&text[0], format, vaList );
    va_end(vaList);

    //
    // TODO: Speed this up....
    //
#if 0    
    if( strlen(stdoutText)+strlen(text) < sizeof(stdoutText) )
    {
        strcat( stdoutText, text );
    }
#endif    
}





