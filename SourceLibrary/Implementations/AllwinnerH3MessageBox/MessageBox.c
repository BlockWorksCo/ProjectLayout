//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "MessageBox.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>




#define readl(addr)                 (*((volatile uint32_t *)(addr)))
#define writel(v, addr)             (readl(addr) = (uint32_t)(v))
#define BIT(nr)                     (1u << (nr))
#define MASK(nr)                    ((1u << (nr)) - 1)
#define MASK_AT(nr, start)          (MASK(nr) << (start))

#define MSGBOX_BASE 		        (0x01c17000)

#define CTRL_REG0                   (messageBoxRegistersBase)
#define CTRL_REG1 		            (messageBoxRegistersBase + 0x04)
#define CTRL_USER0_RECEIVER(n)      (BIT(4) << ((n) * 8))
#define CTRL_USER0_SENDER(n)        (BIT(0) << ((n) * 8))

#define USER0_IRQ_EN_REG 	        (messageBoxRegistersBase + 0x40)
#define USER0_IRQ_STATUS_REG 	    (messageBoxRegistersBase + 0x50)
#define USER1_IRQ_EN_REG 	        (messageBoxRegistersBase + 0x60)
#define USER1_IRQ_STATUS_REG        (messageBoxRegistersBase + 0x70)
#define TRANSMIT_MQn_IRQ_PEND(n)    BIT(2 * (n) + 1)
#define RECEPTION_MQn_IRQ_PEND(n)   BIT(2 * (n))

#define FIFO_STATUS_REG(n)   	    (messageBoxRegistersBase + 0x100 + (n) * 4)
#define MSG_STATUS_REG(n)   	    (messageBoxRegistersBase + 0x140 + (n) * 4)
#define MSG_REG(n)  	 	        (messageBoxRegistersBase + 0x180 + (n) * 4)


//
//
//
uint32_t*   messageBoxRegistersBase = 0;


//
//
//
static uint32_t* MapRegisters(uint32_t baseAddress, uint32_t numberOfBytes)
{
	const unsigned long PAGE_SIZE 		        = 4096;
	const unsigned long GPIO_BASEPage 		    = baseAddress & ~(PAGE_SIZE-1);
	uint32_t 		    GPIO_BASEOffsetIntoPage	= baseAddress - GPIO_BASEPage;
  	int			        mem_fd			        = 0;
  	uint8_t*			regAddrMap 		        = NULL;


	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) 
	{
		perror("can't open /dev/mem");
		exit (1);
	}

  	regAddrMap = (uint8_t*)mmap(
      		NULL,          
      		0xffff,       	
			PROT_READ|PROT_WRITE|PROT_EXEC,// Enable reading & writting to mapped memory
			MAP_SHARED,       //Shared with other processes
      		mem_fd,           
		GPIO_BASEPage);

  	if (regAddrMap == NULL) 
	{
          	perror("mmap error");
          	close(mem_fd);
          	exit (1);
  	}

	return (uint32_t*)(regAddrMap + GPIO_BASEOffsetIntoPage);
}



//
//
//
void MessageBoxInitialise(void)
{
    //
    //
    //
    messageBoxRegistersBase = (uint32_t*)MapRegisters( MSGBOX_BASE, 4096 );

	//clk_enable(CLK_MSGBOX);

	writel(CTRL_USER0_SENDER(0) | CTRL_USER0_RECEIVER(1), CTRL_REG0);
}


//
//
//
bool MessageBoxRead(uint32_t queue, uint32_t* val)
{
	if ((readl(MSG_STATUS_REG(queue)) & 0x07) == 0) 
    {
		return false;
	}
    else
    {
        *val = readl(MSG_REG(queue));
	    return true;
    }


}


//
//
//
bool MessageBoxWrite(uint32_t queue, uint32_t val)
{
	if ((readl(FIFO_STATUS_REG(queue)) & BIT(0)))
    {
		return false;
	}
    else
    {
	    writel(val, MSG_REG(queue));
	    return true;
    }

}





