#======================================================================
MCU		:= atmega16
#======================================================================
SRCS		:=
OBJS		:=
INCS		:=
DEPS		:=
TMPS		:=
LIBS		:=
FIRMWARES	:=
#======================================================================
MKDIR		= mkdir -p
RM		= rm -rf
BUILD_BASE	= Firmware
#======================================================================
# MODULES SRC
MODULES		:= src/system src/driver src/json
# MODULES LIB 
MODULES		+= 
# FIRMWARE
MODULES 	+= 
#======================================================================
# Output format
#======================================================================
FORMAT	:= ihex
#======================================================================
# no user configurable options below here
INCLUDE_DIRS	:= include
vpath %.h $(INCLUDE_DIRS)
#======================================================================
# Common modules
include $(patsubst %, ./%/xmodule.mk, $(MODULES))
#======================================================================
# Current program
include ./Enviroment.mk
include ./avr/atmega16/xmodule.mk
#======================================================================
.PHONY: default build run all clean
all: checkdirs $(FIRMWARES)

build: 

flash:

clean:
	$(RM) $(OBJS) $(DEPS) $(ELF) $(HEX) $(EEP)
	
git: clean
	git push -u origin master	
#======================================================================
# Output file
# Create final output files (.hex, .eep) from ELF
#======================================================================
$(HEX): $(ELF)
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@
	$(SIZE) --format=avr --mcu=$(MCU) $(ELF)
	
$(EEP): $(ELF)
	@echo $(MSG_EEPROM) $@
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom='alloc,load' --change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Link: create ELF output file from object files.
$(ELF): $(OBJS)
	@echo $(MSG_FLASH) $@
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)
#======================================================================
# Compile: create object files from C source files.	
%.deps: %.c %.h
	@$(CC) -MM $< > $@
	
%.o: %.c %.deps
	$(CC) $(CFLAGS) -Os -c $< -o $@

#======================================================================


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	$(Q) mkdir -p $@
