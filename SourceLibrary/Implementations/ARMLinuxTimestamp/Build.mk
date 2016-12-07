
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/ARMLinuxTimestamp


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Interfaces/Timestamp \
                -I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+=	Timestamp.o
    		  		

#
# Libraries.
#
LIBS		+=

