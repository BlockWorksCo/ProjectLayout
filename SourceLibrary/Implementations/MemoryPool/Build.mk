
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/MemoryPool


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/MemoryPool \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/MemoryPool


#
# Objects to build.
#
OBJS		+=	MemoryPool.o
    		  		

#
# Libraries.
#
LIBS		+=

