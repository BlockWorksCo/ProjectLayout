



#ifndef __RADIO_H__
#define __RADIO_H__


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    RadioA,
    RadioB,

} RadioID;



void radioInitialise(RadioID id);

void radioAsyncTransmitPacket(RadioID id, uint8_t* packet, size_t numberOfBytes );
bool radioAsyncTransmitCompleted(RadioID id);

uint32_t radioAsyncReceivePacket(RadioID id, uint8_t* packet, size_t maxPacketSize );
bool radioAsyncReceiveCompleted(RadioID id);


#endif



