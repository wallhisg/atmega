#======================================================================
TARGET		+= atmega16
LOCAL_BUILD_DIR	:= $(BUILD_BASE)/$(TARGET)
BUILD_DIR	+= $(LOCAL_BUILD_DIR)
#======================================================================
LOCAL_BASE	:= avr/atmega16
LOCAL_MDLS	:= 
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

LOCAL_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

SRCS		+= $(LOCAL_SRCS)
OBJS		+= $(LOCAL_OBJS)
DEPS		+= $(LOCAL_DEPS)
#======================================================================
# Create final output files (.hex, .eep) from ELF output file
#======================================================================
FIRM_HEX	+= $(addsuffix .hex, $(TARGET))
LOCAL_FIRM_HEX	:= $(addprefix $(BUILD_DIR)/, $(FIRM_HEX))
HEX		+= $(LOCAL_FIRM_HEX)
FIRM_EEP	+= $(addsuffix .eep, $(TARGET))
LOCAL_FIRM_EEP	:= $(addprefix $(BUILD_DIR)/, $(FIRM_EEP))
EEP		+= $(LOCAL_FIRM_EEP)
FIRM_ELF	+= $(addsuffix .elf, $(TARGET))
LOCAL_FIRM_ELF	:= $(addprefix $(BUILD_DIR)/, $(FIRM_ELF))
ELF		+= $(LOCAL_FIRM_ELF)

FIRMWARE	:= 
FIRMWARE	+= $(ELF)
FIRMWARE	+= $(HEX)
#FIRMWARE	+= $(EEP)

FIRMWARES	+= $(FIRMWARE)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)



