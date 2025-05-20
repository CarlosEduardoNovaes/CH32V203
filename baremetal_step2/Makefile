# ===================================================================================
# Project Makefile
# ===================================================================================
# Project:  CH32V203 Example
# Author:   Stefan Wagner
# Year:     2023
# URL:      https://github.com/wagiminator    
# ===================================================================================
# Install toolchain:
#   sudo apt install build-essential libnewlib-dev gcc-riscv64-unknown-elf
#   sudo apt install python3 python3-pip
#   pip install chprog rvprog
#
# Provide access permission to WCH-LinkE programmer:
#   echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8010", MODE="666"' | sudo tee /etc/udev/rules.d/99-WCH-LinkE.rules
#   echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8012", MODE="666"' | sudo tee -a /etc/udev/rules.d/99-WCH-LinkE.rules
#   sudo udevadm control --reload-rules
#
# Provide access permission to USB bootloader:
#   echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="4348", ATTR{idProduct}=="55e0", MODE="666"' | sudo tee /etc/udev/rules.d/99-ch55x.rules
#   echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="55e0", MODE="666"' | sudo tee -a /etc/udev/rules.d/99-ch55x.rules
#   sudo udevadm control --reload-rules
#
# Type "make flash" in the command line.
# ===================================================================================

# Files and Folders
FIRWARE_DIR     	= bin
TARGET_NAME  			= firmware
STARTUP_DIR  			= startup
LIBRARY_DIR 			= libs
APPLICATION_DIR   = src
BUILD_DIR    			= build


# Microcontroller Settings
CPU_MODEL					:= CH32V203x6
F_CPU   					:= 144000000
LDSCRIPT 					:= ch32v203x6.ld
STARTUP_FILENAME	:= startup_ch32v203.c
CPUARCH  					= -march=rv32imac -mabi=ilp32


# Toolchain
PREFIX   = riscv64-unknown-elf
AR       = $(PREFIX)-ar
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
OBJCOPY  = $(PREFIX)-objcopy
OBJDUMP  = $(PREFIX)-objdump
OBJSIZE  = $(PREFIX)-size
NEWLIB   = /usr/include/newlib
ISPTOOL  = chprog $(FIRWARE_DIR)/$(TARGET_NAME).bin
CLEAN    = rm -f *.lst *.obj *.cof *.list *.map *.eep.hex *.o *.d


# Compiler Flags
OPTIMIZATION_FLAGS 	= -O0 -ffunction-sections -fdata-sections -fno-builtin -flto
DEBUG_FLAGS 		= -g
ARCHITECTURE_FLAGS	= $(CPUARCH) 
DEFINES 			= -DF_CPU=$(F_CPU)
GERNERAL_FLAGS 		= -Wall
INCLUDE_FLAGS			= -I$(NEWLIB) -I$(LIBRARY_DIR) -I$(APPLICATION_DIR) 


CFLAGS   	= $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS)  -L$(BUILD_DIR)/$(LIBRARY_DIR) -nostdlib
#CFLAGS   	= $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS)  -L$(BUILD_DIR)/$(LIBRARY_DIR) 
CFLAGS  	+= $(ARCHITECTURE_FLAGS) $(DEFINES) $(GERNERAL_FLAGS) $(INCLUDE_FLAGS) 
CXXFLAGS  = $(CFLAGS) -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts -x c++
LDFLAGS  	= -T$(STARTUP_DIR)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none



LIBRARY_NAMES 		:=
LIBRARY_FLAGS			:=
LIBRARY_LIST			:=



LIBRARY_SUBDIRS	 := $(filter %/, $(wildcard $(LIBRARY_DIR)/*/))

define include_lib_dir
LIB_CURRENT_DIR			:= $(subst /__,,$(1)__)
LIB_CURRENT_NAME := $(notdir $(subst /__,,$(1)__))
LIBRARY_NAMES 			+= $$(LIB_CURRENT_NAME)
LIBRARY_FLAGS				+= -l$$(LIB_CURRENT_NAME)
include $(firstword $(wildcard $(1)/makefile.mk) libs_failback.mk)
endef


$(foreach dir, $(LIBRARY_SUBDIRS),$(eval $(call include_lib_dir,$(dir))))

$(eval include $(firstword $(wildcard $(APPLICATION_DIR)/makefile.mk) app_failback.mk))

$(eval include $(STARTUP_DIR)/makefile.mk)




$(FIRWARE_DIR)/$(TARGET_NAME).elf:  $(BUILD_DIR)/$(STARTUP_DIR)/startup.o $(APP_SOURCES) $(LIBRARY_LIST)
	@echo "Building $@ ..."
	@mkdir -p $(@D)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) -L$(BUILD_DIR)/$(LIBRARY_DIR)  $(LIBRARY_FLAGS)
	#### $(CXX) -o $@ $(LDFLAGS) $(CXXFLAGS) -L$(BUILD_DIR)/$(LIBRARY_DIR)  $(LIBRARY_FLAGS) -Ilibs  $^ 2> 

$(FIRWARE_DIR)/$(TARGET_NAME).lst: $(FIRWARE_DIR)/$(TARGET_NAME).elf
	@echo "Building $(FIRWARE_DIR)/$(TARGET_NAME).lst ..."
	@$(OBJDUMP) -S $^ > $(FIRWARE_DIR)/$(TARGET_NAME).lst

$(FIRWARE_DIR)/$(TARGET_NAME).map: $(FIRWARE_DIR)/$(TARGET_NAME).elf
	@echo "Building $(FIRWARE_DIR)/$(TARGET_NAME).map ..."
	@$(OBJDUMP) -t $^ > $(FIRWARE_DIR)/$(TARGET_NAME).map

$(FIRWARE_DIR)/$(TARGET_NAME).bin: $(FIRWARE_DIR)/$(TARGET_NAME).elf
	@echo "Building $(FIRWARE_DIR)/$(TARGET_NAME).bin ..."
	@$(OBJCOPY) -O binary $< $(FIRWARE_DIR)/$(TARGET_NAME).bin

$(FIRWARE_DIR)/$(TARGET_NAME).hex: $(FIRWARE_DIR)/$(TARGET_NAME).elf
	@echo "Building $(FIRWARE_DIR)/$(TARGET_NAME).hex ..."
	@$(OBJCOPY) -O ihex $< $(FIRWARE_DIR)/$(TARGET_NAME).hex

$(FIRWARE_DIR)/$(TARGET_NAME).asm: $(FIRWARE_DIR)/$(TARGET_NAME).elf
	@echo "Disassembling to $(FIRWARE_DIR)/$(TARGET_NAME).asm ..."
	@$(OBJDUMP) -d $(FIRWARE_DIR)/$(TARGET_NAME).elf > $(FIRWARE_DIR)/$(TARGET_NAME).asm

size:
	@echo "------------------"
	@echo "FLASH: $(shell $(OBJSIZE) -d $(FIRWARE_DIR)/$(TARGET_NAME).elf | awk '/[0-9]/ {print $$1 + $$2}') bytes"
	@echo "SRAM:  $(shell $(OBJSIZE) -d $(FIRWARE_DIR)/$(TARGET_NAME).elf | awk '/[0-9]/ {print $$2 + $$3}') bytes"
	@echo "------------------"

all:	$(FIRWARE_DIR)/$(TARGET_NAME).elf $(FIRWARE_DIR)/$(TARGET_NAME).lst $(FIRWARE_DIR)/$(TARGET_NAME).map $(FIRWARE_DIR)/$(TARGET_NAME).bin $(FIRWARE_DIR)/$(TARGET_NAME).hex $(FIRWARE_DIR)/$(TARGET_NAME).asm size

clean:
	@echo "Cleaning all up ..."
	@$(CLEAN)
	@rm -rf $(FIRWARE_DIR) $(BUILD_DIR)





print:
	@echo "------------------| Files and Folders |------------------"
	@echo "FIRWARE_DIR          : $(FIRWARE_DIR)"
	@echo "BUILD_DIR            : $(BUILD_DIR)"
	@echo "STARTUP_DIR          : $(STARTUP_DIR)"
	@echo "APPLICATION_DIR      : $(APPLICATION_DIR)" 
	@echo "LIBRARY_DIR          : $(LIBRARY_DIR)"
	@echo "LIBRARY_SUBDIRS      : $(LIBRARY_SUBDIRS)"
	@echo "INCLUDE              : $(INCLUDE)"
	@echo "------------------| Config |------------------"	
	@echo "TARGET_NAME          : $(TARGET_NAME)"		
	@echo "LIBRARY_NAMES        : $(LIBRARY_NAMES)"
	@echo "LIBRARY_FLAGS        : $(LIBRARY_FLAGS)"
	@echo "APP_OBJECTS          : $(APP_OBJECTS)"
	@echo "LIBRARY_LIST         : $(LIBRARY_LIST)"