
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/UARTReceiver


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/UARTReceiver \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/UARTReceiver


#
# Objects to build.
#
OBJS		+=	UARTReceiver.o
    		  		

#
# Libraries.
#
LIBS		+=

