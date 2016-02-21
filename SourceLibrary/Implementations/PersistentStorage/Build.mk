
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/PersistentStorage


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/PersistentStorage \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/PersistentStorage


#
# Objects to build.
#
OBJS		+=	PersistentStorage.o
    		  		

#
# Libraries.
#
LIBS		+=

