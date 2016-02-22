//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "ErrorHandling.h"
#include "BlockedEvents.h"
#include "Utilities.h"


struct
{
    Handler     handler;
    bool*       blockingFlag;

} blockedEventHandlers[8];


void CallWhenUnblocked( Handler handler, bool* blockingFlag )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockedEventHandlers); i++)
    {
        if( blockedEventHandlers[i].handler == 0 )
        {
            blockedEventHandlers[i].handler         = handler;
            blockedEventHandlers[i].blockingFlag    = blockingFlag;
            break;
        }

    }    

}


void CheckBlockedEventHandlers()
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockedEventHandlers); i++)
    {
        if( blockedEventHandlers[i].handler != 0 )
        {
            if( *blockedEventHandlers[i].blockingFlag == true )
            {
                Call( blockedEventHandlers[i].handler );

                blockedEventHandlers[i].handler   = 0;
            }
        }
    }    
}


