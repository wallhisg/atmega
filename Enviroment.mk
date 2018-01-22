#======================================================================
# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf
SIZE	:= avr-size
sizebefore:
	@if [ -f $(TARGET).elf ]; then $(MSG_SIZE_BEFORE); $(ELFSIZE); fi
sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi
#======================================================================	
# AVRDUDE


#======================================================================
# libraries used in this project, mainly provided by the SDK
LIBS		:= -lprintf_flt -lm 
#======================================================================
# compiler flags using during compilation of source files
CFLAGS		:= -Wall -Wno-attributes -g2
CFLAGS		+= -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS		+= -I $(INCLUDE_DIRS)
CFLAGS		+= -DF_CPU=16000000UL
CFLAGS		+= -mmcu=$(MCU) 

# linker flags used to generate the main object file
LDFLAGS		:= -Wl,-u,vfprintf
# select which tools to use as compiler, librarian and linker
CC		:= avr-gcc
OBJCOPY		:= avr-objcopy
#======================================================================
# select which tools to use as compiler, librarian and linker
#======================================================================
AR = ar
ARFLAGS = rv
#======================================================================
V ?= $(VERBOSE)
ifeq ("$(V)","1")
Q :=
vecho := @true
else
Q := @
vecho := @echo
endif
#======================================================================
# Define Messages
#======================================================================
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = -------- end --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
#======================================================================
# Enviroment
#======================================================================
MKDIR		:= mkdir -p
RM		:= rm -f
MV		:= mf -f
#======================================================================
