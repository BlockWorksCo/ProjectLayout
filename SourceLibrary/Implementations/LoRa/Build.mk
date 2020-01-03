
#
# Source directories
#
VPATH		+= $(SOURCE_LIBRARY)/Implementations/LoRa



#
# Include directories.
#
INCLUDES	+= -I$(SOURCE_LIBRARY)/Implementations/LoRa
INCLUDES	+= -I$(SOURCE_LIBRARY)/Interfaces/Radio


#
# Objects to build.
#
OBJS    += sx1276-LoRa.o
OBJS    += sx1276-PhysicalInterface.o


    		  		

#
# Libraries.
#
LIBS		+=

