
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/FLASHDevice


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/FLASHDevice \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/FLASHDevice


#
# Objects to build.
#
OBJS		+=	FLASHDevice.o
    		  		

#
# Libraries.
#
LIBS		+=

