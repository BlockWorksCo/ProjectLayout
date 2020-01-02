
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/BluePillSPIMaster


#
# Include directories.
#
INCLUDES    += -I$(SOURCE_LIBRARY)/Interfaces/SPIMaster
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/BluePillSPIMaster


#
# Objects to build.
#
OBJS		+=	SPIMaster.o
    		  		

#
# Libraries.
#
LIBS		+=

