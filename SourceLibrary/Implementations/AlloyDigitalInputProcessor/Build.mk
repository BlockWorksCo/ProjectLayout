
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/AlloyDigitalInputProcessor


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/AlloyDigitalInputProcessor \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/DigitalInputProcessor \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/HighResolutionTimestamp \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Queue


#
# Objects to build.
#
OBJS		+=	DigitalInputProcessor.o


#
# Libraries.
#
LIBS		+=

