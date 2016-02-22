//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "ErrorHandling.h"
#include "PredicatedEvents.h"
#include "Utilities.h"


struct
{
    Handler     handler;
    bool        (*predicate)();

} predicatedEventHandlers[8];


void CallWhenPredicateIsTrue( Handler handler, bool (*predicate)() )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(predicatedEventHandlers); i++)
    {
        if( predicatedEventHandlers[i].handler == 0 )
        {
            predicatedEventHandlers[i].handler      = handler;
            predicatedEventHandlers[i].predicate    = predicate;
            break;
        }

    }    

}


void CheckPredicatedEventHandlers()
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(predicatedEventHandlers); i++)
    {
        if( predicatedEventHandlers[i].handler != 0 )
        {
            if( predicatedEventHandlers[i].predicate() == true )
            {
                Call( predicatedEventHandlers[i].handler );

                predicatedEventHandlers[i].handler   = 0;
            }
        }
    }    
}