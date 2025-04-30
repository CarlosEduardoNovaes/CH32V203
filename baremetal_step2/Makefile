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
TARGET_NAME  		= firmware
STARTUP_SRC  		= startup
LIBRARY_SRCS 		= libraries
HARDWARE_SRC 		= hw
APPLICATION_SRC 	= src
FIRWARE_DIR     	= bin
BUILD_DIR    		= build

# Microcontroller Settings
F_CPU    			= 144000000
LDSCRIPT 			= ch32v203x6.ld
STARTUP_SOURCE_FILE	= startup_ch32v203
CPUARCH  			= -march=rv32imac -mabi=ilp32


SOURCE_DIRS   		= $(STARTUP_SRC) $(HARDWARE_SRC) $(LIBRARY_SRCS) $(APPLICATION_SRC)
STARTUP_OBJS  		:=
LIBRARY_OBJS 		:=
HARDWARE_OBJS 		:=
APPLICATION_OBJS 	:=
INCLUDE_DIRS  		:=


# Toolchain
PREFIX   = riscv64-unknown-elf
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
OBJCOPY  = $(PREFIX)-objcopy
OBJDUMP  = $(PREFIX)-objdump
OBJSIZE  = $(PREFIX)-size
NEWLIB   = /usr/include/newlib
ISPTOOL  = chprog $(BIN)/$(TARGET).bin
CLEAN    = rm -f *.lst *.obj *.cof *.list *.map *.eep.hex *.o *.d


# Compiler Flags
OPTIMIZATION_FLAGS 	= -O3 -ffunction-sections -fdata-sections -fno-builtin -flto
DEBUG_FLAGS 		= -g
ARCHITECTURE_FLAGS	= $(CPUARCH) 
DEFINES 			= -DF_CPU=$(F_CPU)
GERNERAL_FLAGS 		= -Wall


CFLAGS   	= $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS)  -nostdlib
CFLAGS  	+= $(ARCHITECTURE_FLAGS) $(DEFINES) $(GERNERAL_FLAGS) -I$(NEWLIB) -I$(INCLUDE) -I$(SRC_DIRS) -I.
CXXFLAGS   	= $(CFLAGS) -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts
LDFLAGS  	= -T$(STARTUP)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none

# include subdir function
define include_source_dir
LOCAL_DIR := $1
include $1/makefile.mk
endef

$(foreach dir,$(SOURCE_DIRS),$(eval $(call include_source_dir,$(dir))))




# Symbolic Targets
help:
	@echo "Use the following commands:"
	@echo "make all       compile and build $(TARGET).elf/.bin/.hex/.asm"
	@echo "make hex       compile and build $(TARGET).hex"
	@echo "make asm       compile and disassemble to $(TARGET).asm"
	@echo "make bin       compile and build $(TARGET).bin"
	@echo "make flash     compile and upload to MCU"
	@echo "make clean     remove all build files"


$(BUILD)/add.o: src/add.cxxm
	@echo "Building $@ ..."
	$(CXX) $(CXXFLAGS) -x c++ -c $< -o $@



$(BUILD)/startup.o: $(STARTUP)/$(STARTUP_SRC).c
	@echo "Building $@ ..."
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(FIRWARE_DIR)/$(TARGET_NAME).elf:  $(SRCFILES) $(MODULE_OBJS) $(BUILD)/startup.o
	@echo "Building $(BIN)/$(TARGET).elf ..."
	@mkdir -p $(BIN)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) 

$(BIN)/$(TARGET).lst: $(BIN)/$(TARGET).elf
	@echo "Building $(BIN)/$(TARGET).lst ..."
	@$(OBJDUMP) -S $^ > $(BIN)/$(TARGET).lst

$(BIN)/$(TARGET).map: $(BIN)/$(TARGET).elf
	@echo "Building $(BIN)/$(TARGET).map ..."
	@$(OBJDUMP) -t $^ > $(BIN)/$(TARGET).map

$(BIN)/$(TARGET).bin: $(BIN)/$(TARGET).elf
	@echo "Building $(BIN)/$(TARGET).bin ..."
	@$(OBJCOPY) -O binary $< $(BIN)/$(TARGET).bin

$(BIN)/$(TARGET).hex: $(BIN)/$(TARGET).elf
	@echo "Building $(BIN)/$(TARGET).hex ..."
	@$(OBJCOPY) -O ihex $< $(BIN)/$(TARGET).hex

$(BIN)/$(TARGET).asm: $(BIN)/$(TARGET).elf
	@echo "Disassembling to $(BIN)/$(TARGET).asm ..."
	@$(OBJDUMP) -d $(BIN)/$(TARGET).elf > $(BIN)/$(TARGET).asm

print:
	@echo "------------------| Files and Folders |------------------"
	@echo "TARGET_NAME: 				$(TARGET_NAME)"
	@echo "STARTUP_SRC: 				$(STARTUP_SRC)"
	@echo "LIBRARY_SRCS: 				$(LIBRARY_SRCS)"
	@echo "HARDWARE_SRC: 				$(HARDWARE_SRC)"
	@echo "APPLICATION_SRC: 			$(APPLICATION_SRC)"
	@echo "FIRWARE_DIR: 				$(FIRWARE_DIR)"
	@echo "BUILD_DIR: 					$(BUILD_DIR)"
	@echo "--------------------------------------------------------"
	@echo "--------------| Microcontroller Settings |--------------"
	@echo "F_CPU: 						$(F_CPU)"
	@echo "LDSCRIPT: 					$(LDSCRIPT)"
	@echo "STARTUP_SOURCE_FILE: 		$(STARTUP_SOURCE_FILE)"
	@echo "CPUARCH: 					$(CPUARCH)"
	@echo "--------------------------------------------------------"
	@echo "---------------------| Toolchain |----------------------"
	@echo "PREFIX: 						$(PREFIX)"
	@echo "CC: 							$(CC)"
	@echo "CXX: 						$(CXX)"
	@echo "OBJCOPY: 					$(OBJCOPY)"
	@echo "OBJDUMP: 					$(OBJDUMP)"
	@echo "--------------------------------------------------------"
	@echo "------------------| Compiler Flags |-------------------"
	@echo "CFLAGS: 						$(CFLAGS)"
	@echo "CXXFLAGS: 					$(CXXFLAGS)"
	@echo "LDFLAGS: 					$(LDFLAGS)"
	@echo "--------------------------------------------------------"
	@echo "-------------------| INTERNAL VARS |--------------------"
	@echo "SOURCE_DIRS: 				$(SOURCE_DIRS)"
	@echo "STARTUP_OBJS: 				$(STARTUP_OBJS)"
	@echo "LIBRARY_OBJS: 				$(LIBRARY_OBJS)"
	@echo "HARDWARE_OBJS: 				$(HARDWARE_OBJS)"
	@echo "APPLICATION_OBJS: 			$(APPLICATION_OBJS)"



all:	$(BIN)/$(TARGET).lst $(BIN)/$(TARGET).map $(BIN)/$(TARGET).bin $(BIN)/$(TARGET).hex $(BIN)/$(TARGET).asm size

elf:	$(BIN)/$(TARGET).elf removetemp size

bin:	$(BIN)/$(TARGET).bin removetemp size removeelf

hex:	$(BIN)/$(TARGET).hex removetemp size removeelf

asm:	$(BIN)/$(TARGET).asm removetemp size removeelf

flash:	$(BIN)/$(TARGET).bin size removeelf
	@echo "Uploading to MCU ..."
	@$(ISPTOOL)

clean:
	@echo "Cleaning all up ..."
	@$(CLEAN)
	@rm -f $(BIN)/$(TARGET).elf $(BIN)/$(TARGET).lst $(BIN)/$(TARGET).map $(BIN)/$(TARGET).bin $(BIN)/$(TARGET).hex $(BIN)/$(TARGET).asm
	@rm -f $(BUILD)/*.o

size:
	@echo "------------------"
	@echo "FLASH: $(shell $(OBJSIZE) -d $(BIN)/$(TARGET).elf | awk '/[0-9]/ {print $$1 + $$2}') bytes"
	@echo "SRAM:  $(shell $(OBJSIZE) -d $(BIN)/$(TARGET).elf | awk '/[0-9]/ {print $$2 + $$3}') bytes"
	@echo "------------------"

removetemp:
	@echo "Removing temporary files ..."
	@$(CLEAN)

removeelf:
	@echo "Removing $(BIN)/$(TARGET).elf ..."
	@rm -f $(BIN)/$(TARGET).elf
