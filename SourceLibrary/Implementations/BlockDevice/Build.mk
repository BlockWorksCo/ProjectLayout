
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/BlockDevice


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/BlockDevice \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/BlockDevice


#
# Objects to build.
#
OBJS		+=	BlockDevice.o
    		  		

#
# Libraries.
#
LIBS		+=

