//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#ifndef __I2CMASTER_H__
#define __I2CMASTER_H__

#include "Common.h"


//
//
//
typedef uint8_t     I2CAddress;


//
//
//
void SET_SDA();
void CLEAR_SDA();
bool GET_SDA();

void SET_SCL();
void CLEAR_SCL();



//
//
//
void ResetI2CMaster();
void I2CMasterHandler();

bool I2CMasterByteReceived( uint8_t byte );
void I2CWrite( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes );
void I2CRead( I2CAddress _address, uint8_t* _bytes, uint8_t _numberOfBytes );
void Stop();


#endif



