//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#ifndef __I2CMASTER_H__
#define __I2CMASTER_H__

#include "Platform.h"
#include "EventQueue.h"




void i2cISR();
void Write(uint8_t* _bytes, uint8_t _numberOfBytes, Handler _completionEvent );
void Read( bool (*_byteReceivedCallback)(uint8_t), uint8_t _numberOfBytes , Handler _completionEvent );
void Stop( Handler _completionEvent );



void I2CDisplay();

#endif



