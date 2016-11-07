
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/UARTTransmitter


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/UARTTransmitter \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/UARTTransmitter \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+=	UARTTransmitter.o
    		  		

#
# Libraries.
#
LIBS		+=

