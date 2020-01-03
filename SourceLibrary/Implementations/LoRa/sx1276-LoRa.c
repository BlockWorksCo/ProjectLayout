
#include "Radio.h"
#include "sx1276-LoRa.h"
#include "sx1276-PhysicalInterface.h"
#include "BoardSupport.h"
#include <stdio.h>
#include <string.h>




#define gb_SF  3
#define gb_BW  6
#define CR    0x04
#define CRC_EN   0x00  //CRC Enable



/**********************************************************
**Parameter table define
**********************************************************/
const uint16_t RFM96FreqTbl[3] = {0x066C, 0x0780, 0x0800}; //434MHz  32M¾§Õñ0x066C, 0x0780, 0x0800 	   30M:0x0673, 0x07BB, 0x08BB   {0x85,0x89,0xd9},//26M-TCXO 434M

const uint16_t RFM96PowerTbl[4] =
{
    0x09FF,                   //20dbm
    0x09FC,                   //17dbm
    0x09F9,                   //14dbm
    0x09F6,                   //11dbm
};

const uint8_t RFM96SpreadFactorTbl[6] =
{
    7,8,9,10,11,12
};

const uint8_t RFM96LoRaBwTbl[10] =
{   // 0        1     2       3      4       5         6      7       8      9
//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
    0,1,2,3,4,5,6,7,8,9
};




void loraStandbyMode( SPISlaveID id )
{
    sx1276RegisterWrite( id, LR_RegOpMode+0x01+0x08);                              //Standby
}

void loraSleepMode( SPISlaveID id )
{
    sx1276RegisterWrite( id, LR_RegOpMode+0x00+0x08);                              //Sleep
}

void loraLoraMode( SPISlaveID id )
{
    sx1276RegisterWrite( id, LR_RegOpMode+0x80+0x08);
}


void loraBasicConfiguration( SPISlaveID id, uint8_t mode)
{
    uint8_t i;

    sx1276Reset(id);
    loraSleepMode(id);                                           //Change modem mode Must in Sleep mode
    Delay_ms(1);
    loraLoraMode(id);

    for(i=0; i<3; i++)                                     //setting frequency parameter
    {
        sx1276RegisterWrite( id, RFM96FreqTbl[i]);
    }

    //setting base parameter
    sx1276RegisterWrite( id, RFM96PowerTbl[0]);             //Setting output power parameter
    sx1276RegisterWrite( id, LR_RegOcp+0x0B);                              //RegOcp,Close Ocp
    sx1276RegisterWrite( id, LR_RegLna+0x23);                              //RegLNA,High & LNA Enable

    sx1276RegisterWrite( id, LR_RegModemConfig1+(RFM96LoRaBwTbl[gb_BW]<<4)+(CR<<1)+0x00);//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
    sx1276RegisterWrite( id, LR_RegModemConfig2+(RFM96SpreadFactorTbl[gb_SF]<<4)+(CRC_EN<<2)+0x03);  //SFactor &  LNA gain set by the internal AGC loop

    sx1276RegisterWrite( id, LR_RegSymbTimeoutLsb+0xFF);                   //RegSymbTimeoutLsb Timeout = 0x3FF(Max)

    sx1276RegisterWrite( id, LR_RegPreambleMsb + 0);                       //RegPreambleMsb
    sx1276RegisterWrite( id, LR_RegPreambleLsb + 12);                      //RegPreambleLsb 8+4=12byte Preamble

    sx1276RegisterWrite( id, REG_LR_DIOMAPPING2_LONG+0x01);                     //RegDioMapping2 DIO5=00, DIO4=01

    sx1276RegisterWrite( id, LR_RegIrqFlagsMask+(~(0x40|0x08)));    // TxDone & RxDone.
}

void loraContinuousReceiveMode( SPISlaveID id )
{
    uint8_t addr;

    loraBasicConfiguration(id,0);                                         //setting base parameter

    sx1276RegisterWrite( id, 0x4D00+0x84);                                   //Normal and Rx
    sx1276RegisterWrite( id, LR_RegHopPeriod+0xFF);                          //RegHopPeriod NO FHSS
    sx1276RegisterWrite( id, REG_LR_DIOMAPPING1_LONG+0x01);                       //DIO0=00, DIO1=00, DIO2=00, DIO3=01  DIO0=00--RXDONE

    addr = sx1276RegisterRead( id, (uint8_t)(LR_RegFifoRxBaseAddr>>8));           //Read RxBaseAddr
    sx1276RegisterWrite( id, LR_RegFifoAddrPtr+addr);                        //RxBaseAddr -> FiFoAddrPtr¡¡
    sx1276RegisterWrite( id, LR_RegOpMode+0x0D);                        //Continuous Rx Mode
}




uint8_t loraTransmitPacket_Async(SPISlaveID id, uint8_t *buf,uint8_t len)
{
    sx1276BlockWrite(id, 0x00, (uint8_t *)buf, len);
    sx1276RegisterWrite( id, LR_RegOpMode+0x03+0x08);                    //Tx Mode

    return len;
}


//
// return value is true if a transmit can be started.
//
bool loraCheckAsyncTransmitForCompletion(SPISlaveID id)
{
    if( sx1276IsIRQPinAsserted(id) == true ) 
    {
        uint8_t irqFlags    =  sx1276RegisterRead( id, (uint8_t)(LR_RegIrqFlags>>8));
        if( (irqFlags&0x08) != 0 )
        {
            // Previous transmit is now complete, clear the IRQ flags and
            // move into receive mode.
            sx1276RegisterWrite( id, LR_RegIrqFlags+0x08);
            loraContinuousReceiveMode( id );

            return true;
        }
    }

    return false;
}



bool loraCheckAsyncReceiveCompletion(SPISlaveID id)
{
    if ( sx1276IsIRQPinAsserted(id) == true )
    {
        uint8_t irqFlags    =  sx1276RegisterRead( id, (uint8_t)(LR_RegIrqFlags>>8));
        if( (irqFlags&0x40) != 0 )
        {
            // receive-complete has been signalled.
            return true;
        }
    }

    return false;
}





uint8_t loraReceivePacket( SPISlaveID id, uint8_t* buf, size_t maxBytesToReceive )
{
    memset( &buf[0], 0xff, maxBytesToReceive );

    uint8_t addr = sx1276RegisterRead( id, (uint8_t)(LR_RegFifoRxCurrentaddr>>8)); // last packet addr
    sx1276RegisterWrite( id, LR_RegFifoAddrPtr+addr);                      // RxBaseAddr -> FiFoAddrPtr

    uint8_t length = sx1276RegisterRead( id, (uint8_t)(LR_RegRxNbBytes>>8));        // Number for received bytes

    sx1276BlockRead(id, 0x00, buf, length);

    sx1276RegisterWrite( id, LR_RegIrqFlags+0xFF);
    
    return length;
}   


void loraTransmitPacket( SPISlaveID id, uint8_t* buf, uint8_t size )
{
    uint8_t addr;

    loraBasicConfiguration(id, 0);
    sx1276RegisterWrite( id, 0x4D00+0x87);                      // 20dbm
    sx1276RegisterWrite( id, LR_RegHopPeriod);                  // RegHopPeriod NO FHSS
    sx1276RegisterWrite( id, REG_LR_DIOMAPPING1_LONG+0x41);     // DIO0=01, DIO1=00, DIO2=00, DIO3=01

    sx1276RegisterWrite( id, LR_RegIrqFlags+0xFF);
    sx1276RegisterWrite( id, LR_RegPayloadLength+size);

    // reset the FIFO.
    addr = sx1276RegisterRead( id, (uint8_t)(LR_RegFifoTxBaseAddr>>8)); // RegFiFoTxBaseAddr
    sx1276RegisterWrite( id, LR_RegFifoAddrPtr+addr);                   // RegFifoAddrPtr

    sx1276RegisterRead( id, (uint8_t)(LR_RegPayloadLength>>8) );

    loraTransmitPacket_Async(id, buf,size);
}   



void radioInitialise(RadioID id)
{
    sx1276PhysicalInterfaceInit( (SPISlaveID)id );
    loraContinuousReceiveMode( (SPISlaveID)id );
}

void radioAsyncTransmitPacket(RadioID id, uint8_t* packet, size_t numberOfBytes )
{
    loraTransmitPacket( (SPISlaveID)id, packet, numberOfBytes );
}

bool radioAsyncTransmitCompleted(RadioID id)
{
    return loraCheckAsyncTransmitForCompletion( (SPISlaveID)id );
}

uint32_t radioAsyncReceivePacket(RadioID id, uint8_t* packet, size_t maxPacketSize )
{
    return loraReceivePacket( (SPISlaveID)id, packet, maxPacketSize );
}

bool radioAsyncReceiveCompleted(RadioID id)
{
    return loraCheckAsyncReceiveCompletion( (SPISlaveID)id );
}



