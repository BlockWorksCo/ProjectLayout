//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __UNITTEST_H__
#define __UNITTEST_H__


#include "Common.h"

#define MAX_TESTS           (128)



#define TEST_ASSERT( test , message );  		Assert( test, message, __FILE__, __LINE__ )

//
//
//
typedef void (*TestFunction)();


//
//
//
void AddTest( char* name, TestFunction fn );
void RunTests( char* suiteName );
void UnitTestResultPrintf( char* format, ...);

void Assert( bool test, char* message, char* fileName, uint32_t lineNumber );


#endif


