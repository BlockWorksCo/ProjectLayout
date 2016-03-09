
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/AlloyHighResolutionTimestamp


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/AlloyHighResolutionTimestamp \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/HighResolutionTimestamp


#
# Objects to build.
#
OBJS		+=	HighResolutionTimestamp.o


#
# Libraries.
#
LIBS		+=

