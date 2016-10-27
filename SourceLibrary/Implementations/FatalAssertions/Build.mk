
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/FatalAssertions


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/FatalAssertions \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Assertions \
				-I$(SOURCE_LIBRARY)/Interfaces/ErrorHandling


#
# Objects to build.
#
OBJS		+=	Assertions.o
    		  		

#
# Libraries.
#
LIBS		+=

