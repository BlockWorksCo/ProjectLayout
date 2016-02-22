//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "UnitTest.h"
#include "Utilities.h"
#include "ErrorHandling.h"


//
//
//
typedef struct
{
    TestFunction    fn;
    char*           name;

} TestTableEntry;

TestTableEntry  testTable[MAX_TESTS]    = {0};
uint8_t         testCount               = 0;




//
//
//
void AddTest( char* name, TestFunction fn )
{
    for(uint8_t i=0; i<NUMBER_OF_ELEMENTS(testTable); i++)
    {
        if(testTable[i].fn == 0)
        {
            testTable[i].fn     = fn;
            testTable[i].name   = name;
            testCount++;
            return;
        }
    }

    PANIC();
}


static char     stdoutText[1024*16];


void UnitTestResultPrintf( char* format, ...)
{
    static char     text[256];
    va_list         vaList;

    //
    // Form the text to store.
    //
    va_start(vaList, format);
    memset(&text[0], 0, sizeof(text));
    vsprintf(&text[0], format, vaList );
    va_end(vaList);

    //
    // TODO: Speed this up....
    //
    if( strlen(stdoutText)+strlen(text) < sizeof(stdoutText) )
    {
        strcat( stdoutText, text );
    }
}



void Assert( bool test, char* message, char* fileName, uint32_t lineNumber )
{
    if( test == false )
    {
        DPRINTF("\t\t<failure name=\"%s\" classname=\"main\" time=\"1\" position=\"%s:%d\" >\r\n", message, fileName, lineNumber );
        DPRINTF("\t\t</failure>\r\n");
    }
}


//
//
//
void RunTests( char* suiteName )
{
    DPRINTF("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    DPRINTF("<testsuite failures=\"0\" tests=\"%d\" name=\"%s\">\r\n", testCount, suiteName );
    for(uint8_t i=0; i<NUMBER_OF_ELEMENTS(testTable); i++)
    {
        if(testTable[i].fn != 0)
        {
            memset( &stdoutText[0], 0x00, sizeof(stdoutText) );

            DPRINTF("\t<testcase name=\"%s\" classname=\"%s\" time=\"0\" >\n", testTable[i].name, testTable[i].name );
            testTable[i].fn();
            if(strlen(stdoutText) > 0)
            {
                DPRINTF("\t\t<system-out>%s</system-out>\r\n", stdoutText );                
            }
            DPRINTF("\t</testcase>\r\n");
        }
    }
    DPRINTF("</testsuite>\r\n");
}



