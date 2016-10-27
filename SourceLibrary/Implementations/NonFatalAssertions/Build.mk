
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/NonFatalAssertions


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/NonFatalAssertions \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Assertions


#
# Objects to build.
#
OBJS		+=	Assertions.o
    		  		

#
# Libraries.
#
LIBS		+=

