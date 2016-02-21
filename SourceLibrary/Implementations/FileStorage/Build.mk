
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/FileStorage


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/FileStorage \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/FileStorage


#
# Objects to build.
#
OBJS		+=	FileStorage.o
    		  		

#
# Libraries.
#
LIBS		+=

