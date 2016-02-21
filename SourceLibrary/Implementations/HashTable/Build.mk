
#
# Source directories
#
VPATH		+=	$(SOURCE_LIBRARY)/Implementations/HashTable


#
# Include directories.
#
INCLUDES	+=	-I$(SOURCE_LIBRARY)/Implementations/HashTable \
        	  	-I$(SOURCE_LIBRARY)/Interfaces/HashTable


#
# Objects to build.
#
OBJS		+=	HashTable.o
    		  		

#
# Libraries.
#
LIBS		+=

