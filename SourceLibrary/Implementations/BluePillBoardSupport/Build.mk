
#
# Source directories
#
VPATH		+= $(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport
VPATH       += $(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/stm_lib/src
VPATH       += $(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/cmsis
VPATH       += $(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/cmsis_boot
VPATH       += $(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/cmsis_boot/startup



#
# Include directories.
#
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/stm_lib/inc
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/cmsis
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/BluePillBoardSupport/cmsis_boot
INCLUDES    += -I$(SOURCE_LIBRARY)/Interfaces/BoardSupport
INCLUDES    += -I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+= BoardSupport.o
OBJS        += system_stm32f10x.o
OBJS        += startup_stm32f10x_md.o
OBJS        += stm32f10x_rcc.o
OBJS        += stm32f10x_gpio.o
OBJS        += stm32f10x_spi.o
OBJS        += stm32f10x_tim.o

    		  		

#
# Libraries.
#
LIBS		+=


CFLAGS  += -DSTM32F103C8
CFLAGS  += -DSTM32F10X_MD
CFLAGS  += -DUSE_SX1276_RADIO
CFLAGS  += -DUSE_STDPERIPH_DRIVER
CFLAGS  += -g
CFLAGS  += -mcpu=cortex-m3
CFLAGS  += -mthumb -mabi=aapcs --std=c99
CFLAGS  += -Wall -Werror -O0
CFLAGS  += -mfloat-abi=soft
CFLAGS  += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS  += -fno-builtin --short-enums

LDFLAGS += -L../
LDFLAGS += -mthumb -mabi=aapcs -T../stm32f10x.ld
LDFLAGS += -mcpu=cortex-m3
LDFLAGS += -Wl,--gc-sections
LDFLAGS += --specs=nano.specs -lc -lnosys

