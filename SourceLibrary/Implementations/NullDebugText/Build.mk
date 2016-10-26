
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/NullDebugText


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/NullDebugText \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/DebugText \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+=	DebugText.o
    		  		

#
# Libraries.
#
LIBS		+=

