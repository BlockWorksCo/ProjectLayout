
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/LinuxBoardSupport


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/LinuxBoardSupport \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/BoardSupport \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Common


#
# Objects to build.
#
OBJS		+=	BoardSupport.o
    		  		

#
# Libraries.
#
LIBS		+=

