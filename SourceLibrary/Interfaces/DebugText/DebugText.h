


#ifndef __DEBUGTEXT_H__
#define __DEBUGTEXT_H__


#include "Common.h"


void DebugTextOutput(const char* text);
void DebugPrintf(const char* format, ...);
void DebugHexDumpBytes( const uint8_t* data, uint32_t numberOfBytes );
void DebugHexDumpWords( const uint8_t* data, uint32_t numberOfBytes );


#endif

