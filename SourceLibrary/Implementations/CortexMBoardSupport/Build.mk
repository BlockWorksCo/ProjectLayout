
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/CortexMBoardSupport


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/CortexMBoardSupport \
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

