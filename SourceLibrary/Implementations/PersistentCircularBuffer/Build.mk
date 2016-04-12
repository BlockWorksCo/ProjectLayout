
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/PersistentCircularBuffer


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/PersistentCircularBuffer \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/PersistentCircularBuffer


#
# Objects to build.
#
OBJS		+=	PersistentCircularBuffer.o
    		  		

#
# Libraries.
#
LIBS		+=

