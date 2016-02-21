
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/LogStorage


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/LogStorage \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/LogStorage


#
# Objects to build.
#
OBJS		+=	LogStorage.o
    		  		

#
# Libraries.
#
LIBS		+=

