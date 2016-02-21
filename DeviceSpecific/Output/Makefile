#
#
#


#
# Make sure we do something sensible if no target is specified.
#
.DEFAULT_GOAL := all
.SUFFIXES: .c .h .o
SHELL		= sh


#########################################################################################################

#
# Tools
#
CPPC      		= arm-none-eabi-g++
CC        	    = arm-none-eabi-gcc
LD        		= arm-none-eabi-gcc
OBJCOPY   		= arm-none-eabi-objcopy
RM        		= rm
MKDIR     		= mkdir
SIZE      		= size
HEX2BIN   		= hex2bin
ECHO      		= echo
ECHO_RED  		= echo -e "\033[0;31m"
ECHO_GREEN		= echo -e "\033[0;32m"


#
# Build flags.
#
CFLAGS      = -O2 -g 
LDFLAGS	    = -g


#########################################################################################################


include $(PROJECT_BASE)/Firmware/Build.mk
include $(SOURCE_LIBRARY)/Implementations/asn1der/Build.mk


#
# Note: this line is only here because it *MUST* appear after -lZecc_sect283k1 otherwise you get multiple definitions
# of memset & memcpy as they are alse defined in libZecc_sect283k1! argh....
#
LIBS		+= -lcr_c -lcr_eabihelpers -lcr_nohost -lnosys


#########################################################################################################


#
# Include the dependency rules for each target iff already generated.
# If they haven't been generated, then we have to build anyway.
#
-include $(notdir $(patsubst %.o,%.d,$(OBJS)) )


#########################################################################################################


#
# Default target.
#
all: Main.elf


#
# Remove all the build artifacts.
#
clean:
	@ $(ECHO) Cleaning.
	-@ $(RM) -f *.d
	-@ $(RM) -f *.o
	-@ $(RM) -f *.a
	-@ $(RM) -f *.bin
	-@ $(RM) -f *.hex
	-@ $(RM) -f *.elf


#
# Link the objects into a binary.
#
Main.elf: $(OBJS)
	@ $(LD) $(LDFLAGS) -Xlinker -Map=$@.map -o $@ $^ $(LIBS)
	@ $(SIZE) -d $@

#
# Split the .elf into memory regions and then recombine into a .bin that the bootloader understands.
#
Main.bin: Main.elf
	@ $(ECHO) Creating binary image $@
	@ $(OBJCOPY) -S -O ihex $< Main.hex
	@ $(HEXSPLIT) Main.hex $(HEX2BIN)

#########################################################################################################


#
# Compile a file and then generate its dependencies.
#
%.o: %.c
	@ $(ECHO) Building $(basename $<)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@ $(CC) -MM $(CFLAGS) $(INCLUDES) $< -o $(notdir $(patsubst %.o,%.d,$@) )


