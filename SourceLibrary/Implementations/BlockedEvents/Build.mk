
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/BlockedEvents


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/BlockedEvents \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/BlockedEvents \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/Utilities


#
# Objects to build.
#
OBJS		+=	BlockedEvents.o
    		  		

#
# Libraries.
#
LIBS		+=

