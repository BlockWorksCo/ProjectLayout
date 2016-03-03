
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/AlloyThreadLocalStorage


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/AlloyThreadLocalStorage \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/ThreadLocalStorage


#
# Objects to build.
#
OBJS		+=	ThreadLocalStorage.o

#
# Libraries.
#
LIBS		+=

