

#include "Common.h"
#include "ErrorHandling.h"
#include "BoardSupport.h"

#include "sx1276-PhysicalInterface.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"




/**********************************************************
**Name:     sx1276RegisterRead
**Function: SPI Read CMD
**Input:    adr -> address for read
**Output:   None
**********************************************************/
uint8_t sx1276RegisterRead( SPISlaveID id, uint8_t adr)
{
    uint8_t tmp;

    spiBusSelectSlave( id );

    spiBusWriteOneByte(adr&0x7f);
    tmp = spiBusReadOneByte();

    spiBusDeselectSlave( id );

    return(tmp);
}

/**********************************************************
**Name:     sx1276RegisterWrite
**Function: SPI Write CMD
**Input:    WrPara -> address & data
**Output:   None
**********************************************************/
void sx1276RegisterWrite( SPISlaveID id, uint16_t WrPara)
{
    spiBusSelectSlave( id );

    WrPara |= 0x8000;
    spiBusWriteOneByte(WrPara>>8);//    15->0
    spiBusWriteOneByte((uint8_t)WrPara);

    spiBusDeselectSlave( id );
}


/**********************************************************
**Name:     sx1276BlockRead
**Function: SPI burst read mode
**Input:    adr-----address for read
**          ptr-----data buffer point for read
**          length--how many bytes for read
**Output:   None
**********************************************************/
void sx1276BlockRead( SPISlaveID id, uint8_t adr, uint8_t *ptr, uint8_t length)
{
    uint8_t i;
    if(length<=1)                                            //lengt
    {
        return;
    }
    else
    {
        spiBusSelectSlave( id );

        spiBusWriteOneByte(adr&0x7f);
        for(i=0; i<length; i++)
        {
            ptr[i] = spiBusWriteOneByte(0xff);
        }

        spiBusDeselectSlave( id );
    }
}


/**********************************************************
**Name:     SPIsx1276BlockWrite
**Function: SPI burst write mode
**Input:    adr-----address for write
**          ptr-----data buffer point for write
**          length--how many bytes for write
**Output:   none
**********************************************************/
void sx1276BlockWrite( SPISlaveID id, uint8_t adr, uint8_t *ptr, uint8_t length)
{
    spiBusSelectSlave( id );

    spiBusWriteOneByte(adr|0x80);
    for(uint8_t i=0; i<length; i++)
    {
        spiBusWriteOneByte(ptr[i]);
    }

    spiBusDeselectSlave( id );
}


bool sx1276IsIRQPinAsserted(SPISlaveID id)
{
    if(id == SlaveA) {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) != 0) {
            return true;
        }
        else {
            return false;
        }
    }

    if(id == SlaveB) {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) != 0) {
            return true;
        }
        else {
            return false;
        }
    }

    PANIC("Unimplemented");
    return false;
}



void sx1276Reset( SPISlaveID id )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if( id == SlaveA ) 
    {
        // Set RESET pin to 0
        GPIO_WriteBit( GPIOB, GPIO_Pin_12, Bit_RESET );
        // Configure RESET as output
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_Init( GPIOB, &GPIO_InitStructure );

        GPIOB->ODR &= ~GPIO_Pin_12;
    
        Delay_ms(1);

        // Configure RESET as input
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
        GPIO_Init( GPIOB, &GPIO_InitStructure );

        GPIOB->ODR |= GPIO_Pin_12;
    }

    if( id == SlaveB ) 
    {
        // Set RESET pin to 0
        GPIO_WriteBit( GPIOB, GPIO_Pin_13, Bit_RESET );
        // Configure RESET as output
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_Init( GPIOB, &GPIO_InitStructure );

        GPIOB->ODR &= ~GPIO_Pin_13;

        Delay_ms(1);

        // Configure RESET as input
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
        GPIO_Init( GPIOB, &GPIO_InitStructure );

        GPIOB->ODR |= GPIO_Pin_13;
    }

    Delay_ms(10);
}





void sx1276PhysicalInterfaceInit(SPISlaveID id )
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Initialize Button input PB10 PB11*/
    // Enable PORTB Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Configure the GPIO_BUTTON pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    /* Initialize DIO input PB10 PB11*/
    // Enable PORTB Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Configure the GPIO_BUTTON pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // B12 B13 are resets
    // B10 B11 are DIO0 inputs.

    spiBusInit();
}




