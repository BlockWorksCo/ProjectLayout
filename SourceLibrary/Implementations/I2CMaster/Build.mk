
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/I2CMaster


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/I2CMaster \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/I2CMaster


#
# Objects to build.
#
OBJS		+=	I2CMaster.o
    		  		

#
# Libraries.
#
LIBS		+=

