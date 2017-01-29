
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/CircularBuffer


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/CircularBuffer \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/CircularBuffer \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Utilities


#
# Objects to build.
#
OBJS		+=	CircularBuffer.o
    		  		

#
# Libraries.
#
LIBS		+=

