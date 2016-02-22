
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/Utilities


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/Utilities \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Utilities \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/DebugText


#
# Objects to build.
#
OBJS		+=	Utilities.o
    		  		

#
# Libraries.
#
LIBS		+=

