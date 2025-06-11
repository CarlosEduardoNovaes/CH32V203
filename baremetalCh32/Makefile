TOOLCHAIN_URL  := https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz
TOOLCHAIN_TAR  := $(notdir $(TOOLCHAIN_URL))
TOOLCHAIN_TEMP := xpack-riscv-none-elf-gcc-14.2.0-3

toolchain:
	@echo "==> Downloading RISC-V toolchain..."
	@wget -cq $(TOOLCHAIN_URL)
	@echo "==> Extracting toolchain..."
	@tar -xf $(TOOLCHAIN_TAR)
	@mv -f $(TOOLCHAIN_TEMP) $@
	@rm $(TOOLCHAIN_TAR)
	@echo "==> Toolchain ready in ./$@"

# Toolchain
#$PREFIX   = riscv64-unknown-elf
TOOLCHAIN_PREFIX   = ~/.local/xPacks/riscv-none-elf-gcc-14.2.0-3/bin/riscv-none-elf
TOOLCHAIN_AR       = $(TOOLCHAIN_PREFIX)-ar
TOOLCHAIN_CC       = $(TOOLCHAIN_PREFIX)-gcc
TOOLCHAIN_CXX      = $(TOOLCHAIN_PREFIX)-g++
TOOLCHAIN_OBJCOPY  = $(TOOLCHAIN_PREFIX)-objcopy
TOOLCHAIN_OBJDUMP  = $(TOOLCHAIN_PREFIX)-objdump
TOOLCHAIN_OBJSIZE  = $(TOOLCHAIN_PREFIX)-size
NEWLIB   = /usr/include/newlib
ISPTOOL  = chprog $(FIRWARE_DIR)/$(TARGET_NAME).bin
CLEAN    = rm -f *.lst *.obj *.cof *.list *.map *.eep.hex *.o *.d


# Microcontroller Settings
CPU_MODEL					:= CH32V203x6
F_CPU   					:= 144000000
LDSCRIPT 					:= ch32v203x6.ld
CPUARCH  					= -march=rv32imac -mabi=ilp32

# Files and Folders
DIRS_FIRMWARE			:= firmware
DIRS_BUILD        := build
DIRS_STARTUP     	:= startup
DIRS_LIBRARIES    := libs
DIRS_SOURCE       := src


# Compiler Flags
CCFLAGS_OPTIMIZATION 	= -O3 -ffunction-sections -fdata-sections -fno-builtin -flto
CCFLAGS_DEBUG	 				= -g
CCFLAGS_ARCHITECTURE  = $(CPUARCH) 
CCFLAGS_DEFINES      	= -DF_CPU=$(F_CPU)
CCFLAGS_GENERAL       = -Wall
CCFLAGS_INCLUDES      = -I$(NEWLIB) -I$(LIBRARY_DIR) -I$(APPLICATION_DIR)


CCFLAGS     =  $(CCFLAGS_DEBUG) $(CCFLAGS_OPTIMIZATION)  -L$(BUILD_DIR)/$(LIBRARY_DIR) -nostdlib
CCFLAGS     += $(CCFLAGS_ARCHITECTURE) $(CCFLAGS_DEFINES) $(CCFLAGS_GENERAL) $(CCFLAGS_INCLUDES) 
CXXFLAGS    = $(CFLAGS) -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts -x c++
LDFLAGS  	  = -T$(STARTUP_DIR)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none


define include_component_dir
CURRENT_INCLUDE_DIR 	:=$(1)
include $(1)/makefile.mk
endef

$(eval $(call include_component_dir,$(DIRS_STARTUP)))
$(eval $(call include_component_dir,$(DIRS_SOURCE)))







