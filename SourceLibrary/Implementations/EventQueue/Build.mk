
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/EventQueue


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/EventQueue \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/EventQueue


#
# Objects to build.
#
OBJS		+=	EventQueue.o
    		  		

#
# Libraries.
#
LIBS		+=

