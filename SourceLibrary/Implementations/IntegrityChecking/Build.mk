
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/IntegrityChecking


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/IntegrityChecking \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/IntegrityChecking


#
# Objects to build.
#
OBJS		+=	IntegrityChecking.o
    		  		

#
# Libraries.
#
LIBS		+=

