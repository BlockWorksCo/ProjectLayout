
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/KeyValueStore


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/KeyValueStore \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/KeyValueStore


#
# Objects to build.
#
OBJS		+=	KeyValueStore.o
    		  		

#
# Libraries.
#
LIBS		+=

