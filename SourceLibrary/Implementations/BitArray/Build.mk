
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/BitArray


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Interfaces/BitArray \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Utilities


#
# Objects to build.
#
OBJS		+=	BitArray.o
    		  		

#
# Libraries.
#
LIBS		+=

