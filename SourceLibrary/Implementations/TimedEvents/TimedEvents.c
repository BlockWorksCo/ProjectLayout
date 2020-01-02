//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "ErrorHandling.h"
#include "TimedEvents.h"
#include "BoardSupport.h"


struct
{
    Handler     handler;
    uint32_t    interval;
    uint32_t    firingTime;

} timedEventHandlers[8] = {0};


void CallEvery_ms( Handler handler, uint32_t interval )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(timedEventHandlers); i++)
    {
        if( timedEventHandlers[i].handler == 0 )
        {
            timedEventHandlers[i].handler       = handler;
            timedEventHandlers[i].interval      = interval;
            timedEventHandlers[i].firingTime    = CurrentTimestamp_ms() + interval;
            break;
        }

    }
}

void CallAfter_ms( Handler handler, uint32_t interval )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(timedEventHandlers); i++)
    {
        if( timedEventHandlers[i].handler == 0 )
        {
            timedEventHandlers[i].handler       = handler;
            timedEventHandlers[i].interval      = 0;
            timedEventHandlers[i].firingTime    = CurrentTimestamp_ms() + interval;
            break;
        }

    }    
}


void CheckTimedEventHandlers()
{
    uint32_t    timestamp   = CurrentTimestamp_ms();

    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(timedEventHandlers); i++)
    {
        if( timedEventHandlers[i].handler != 0 )
        {
            if( timestamp >= timedEventHandlers[i].firingTime )
            {
                Call( timedEventHandlers[i].handler );

                if(timedEventHandlers[i].interval == 0)
                {
                    timedEventHandlers[i].handler   = 0;
                }
                else
                {
                    timedEventHandlers[i].firingTime    = timestamp + timedEventHandlers[i].interval;                    
                }
            }
        }
    }    
}







