//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, January 2020.
//




#ifndef __SPIMASTER_H__
#define __SPIMASTER_H__

#include "Common.h"


//
//
//
typedef enum
{
    SlaveA,
    SlaveB,
    SlaveC,
    SlaveD,
    SlaveE,
    SlaveF,

} SPISlaveID;



void spiBusInit();
 
void spiBusSelectSlave( SPISlaveID slaveID );
 
void spiBusDeselectSlave( SPISlaveID slaveID );
 
uint8_t spiBusWriteOneByte( uint8_t byte );
 
uint8_t spiBusReadOneByte();


#endif



