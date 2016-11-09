

THIS_MAKEFILE_PATH  := $(dir $(lastword $(MAKEFILE_LIST)))

#
# Source directories
#
VPATH		+=  $(THIS_MAKEFILE_PATH)


#
# Include directories.
#
INCLUDES	+=	-I$(THIS_MAKEFILE_PATH)


#
# Objects to build.
#
OBJS		+=	Main.o
    		  		

#
# Libraries.
#
LIBS		+=

