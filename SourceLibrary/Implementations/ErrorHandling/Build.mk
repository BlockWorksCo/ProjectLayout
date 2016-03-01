
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/ErrorHandling


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/ErrorHandling \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/ErrorHandling \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+=	ErrorHandling.o
    		  		

#
# Libraries.
#
LIBS		+=

