
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/LinuxSharedMemory


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Interfaces/SharedMemory \
                -I$(SOURCE_LIBRARY)/Interfaces/ErrorHandling


#
# Objects to build.
#
OBJS		+=	SharedMemory.o
    		  		

#
# Libraries.
#
LIBS		+=

