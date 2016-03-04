
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/BitStreamCompressor


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Interfaces/BitStreamCompressor \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Utilities


#
# Objects to build.
#
OBJS		+=	BitStreamCompressor.o
    		  		

#
# Libraries.
#
LIBS		+=

