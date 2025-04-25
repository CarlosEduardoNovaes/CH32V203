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
TARGET   = firmware
INCLUDE  = include
STARTUP  = startup
SRC_DIRS   = src
BIN      = bin
BUILD    = build

# Microcontroller Settings
F_CPU    	= 144000000
LDSCRIPT 	= ch32v203x6.ld
STARTUP_SRC = startup_ch32v203
CPUARCH  	= -march=rv32imac -mabi=ilp32

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
CFLAGS   	= -g -O3 -flto -ffunction-sections -fdata-sections -fno-builtin -nostdlib
CFLAGS  	+= $(CPUARCH) -DF_CPU=$(F_CPU) -I$(NEWLIB) -I$(INCLUDE) -I$(SRC_DIRS) -I. -Wall
CXXFLAGS   	= -g -O3 -flto -ffunction-sections -fdata-sections -fno-builtin -nostdlib
CXXFLAGS  	+= $(CPUARCH) -DF_CPU=$(F_CPU) -I$(NEWLIB) -I$(INCLUDE) -I$(SRC_DIRS) -I. -Wall -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts
LDFLAGS  	= -T$(STARTUP)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none
SRCFILES   	= src/main.cxx src/system.cxx

# Arquivos de módulos
MODULE_SRCS = src/add.cxxm

# Geração dos arquivos .o correspondentes na pasta build
MODULE_OBJS = $(BUILD)/add.o



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

$(BIN)/$(TARGET).elf:  $(SRCFILES) $(MODULE_OBJS) $(BUILD)/startup.o
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
	@echo "SRCFILES: $(SRCFILES)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "ISPTOOL: $(ISPTOOL)"
	@echo "CLEAN: $(CLEAN)"
	@echo "BIN: $(BIN)"
	@echo "BUILD: $(BUILD)"
	@echo "TARGET: $(TARGET)"
	@echo "STARTUP_SRC: $(STARTUP_SRC)"
	@echo "STARTUP: $(STARTUP)"
	@echo "SRC_DIRS: $(SRC_DIRS)"
	@echo "INCLUDE: $(INCLUDE)"
	@echo "MODULE_SRCS: $(MODULE_SRCS)"
	@echo "MODULE_OBJS: $(MODULE_OBJS)"


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
