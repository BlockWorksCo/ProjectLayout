


#ifndef __THREADLOCALSTORAGE_H__
#define __THREADLOCALSTORAGE_H__



//
//
//
typedef struct
{
    CoreMessage             message;
    uint32_t                numberOfMessagesAvailable;
    
} GlobalData;


GlobalData* Globals();



#endif

