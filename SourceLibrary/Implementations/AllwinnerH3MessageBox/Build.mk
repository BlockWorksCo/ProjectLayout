
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/AllwinnerH3MessageBox


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/AllwinnerH3MessageBox \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/MessageBox


#
# Objects to build.
#
OBJS		+=	MessageBox.o
    		  		

#
# Libraries.
#
LIBS		+=

