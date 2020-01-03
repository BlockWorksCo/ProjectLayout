



#ifndef __RADIO_H__
#define __RADIO_H__





void radioInitialise();

void radioAsyncTransmitPacket( uint8_t* packet, size_t numberOfBytes );
bool radioAsyncTransmitCompleted();

void radioAsyncReceivePacket( uint8_t* packet, size_t maxPacketSize );
bool radioAsyncReceiveCompleted();


#endif



