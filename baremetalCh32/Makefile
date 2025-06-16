# PROJECT CONFIGURATION
PROJECT_NAME			          := baremetal
PROJECT_DEPENDENCIES        := pinled registers system


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
ISPTOOL  = chprog $(DIRS_FIRMWARE)/$(PROJECT_NAME).bin

# Files and Folders
DIRS_FIRMWARE               := firmware
DIRS_BUILD                  := build
DIRS_STARTUP                := startup
DIRS_LIBRARIES              := libs
DIRS_SOURCE                 := src



# Microcontroller Settings
CPU_MODEL                   := CH32V203x6
F_CPU                       := 144000000
LDSCRIPT                    := ch32v203x6.ld
CPUARCH                     := -march=rv32imac -mabi=ilp32
STARTUP_FILENAME            := startup_ch32v203.c




# Compiler Flags
CCFLAGS_OPTIMIZATION 	= -O3 -ffunction-sections -fdata-sections -fno-builtin -flto
CCFLAGS_DEBUG	 				= 
CCFLAGS_ARCHITECTURE  = $(CPUARCH) 
CCFLAGS_DEFINES      	= -DF_CPU=$(F_CPU)
CCFLAGS_GENERAL       = -Wall -nostdlib
CCFLAGS_INCLUDES      = -I$(NEWLIB) -I$(DIRS_SOURCE)


CCFLAGS     =  $(CCFLAGS_DEBUG) $(CCFLAGS_OPTIMIZATION) 
CCFLAGS     += $(CCFLAGS_ARCHITECTURE) $(CCFLAGS_DEFINES) $(CCFLAGS_GENERAL) $(CCFLAGS_INCLUDES) 
CXXFLAGS    = -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts '-fmodule-mapper=|@g++-mapper-server -r'$(DIRS_BUILD)/gcm.cache  $(CCFLAGS)
LDFLAGS  	  = -T$(DIRS_STARTUP)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none




# Lista acumulada de dependências (com deduplicação)
ALL_DEPENDENCIES :=

# Função para resolver dependências recursivamente
define scan_dependencies
  $(foreach dep,$(1),\
    $(if $(filter $(dep),$(ALL_DEPENDENCIES)),,\
			$(eval CURRENT_COMPONENT := $(dep)) \
			$(eval CURRENT_COMPONENT_DIRECTORY := $(DIRS_LIBRARIES)/$(dep)) \
			$(eval CURRENT_TARGET := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/lib$(dep).a) \
			$(eval CURRENT_TARGET_DIRECTORY := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/$(dep)) \
      $(eval include $(DIRS_LIBRARIES)/$(dep)/makefile.mk) \
      $(call scan_dependencies,$(COMPONENT_DEPENDENCIES)) \
			$(eval ALL_DEPENDENCIES += $(dep)) \
    )\
  )
endef


# Gatilho para resolver as dependências
$(eval $(call scan_dependencies,$(PROJECT_DEPENDENCIES)))

# Geração automática dos diretórios de inclusão
DEPENDENCIES_INCLUDE_DIRS := $(addprefix -Ilibs/, $(addsuffix /include, $(ALL_DEPENDENCIES)))
DEPENDENCIES_LIBRARY_DIRS := $(addprefix -L$(DIRS_BUILD)/libs/, $(ALL_DEPENDENCIES))
DEPENDENCIES_LIBRARY_FLAGS := $(addprefix -l, $(ALL_DEPENDENCIES))
DEPENDENCIES_OBJECTS := $(addprefix $(DIRS_BUILD)/libs/lib, $(addsuffix .a, $(ALL_DEPENDENCIES)))



# Exemplo de uso
print:
	@echo "Projeto usa: $(PROJECT_DEPENDENCIES)"
	@echo "Lista de todas as dependências : $(ALL_DEPENDENCIES)"
	@echo "Includes para o compilador: $(DEPENDENCIES_INCLUDE_DIRS)"
	@echo "LIB DIRS para o compilador: $(DEPENDENCIES_LIBRARY_DIRS)"
	@echo "LIB flags para o compilador: $(DEPENDENCIES_LIBRARY_FLAGS)"
	@echo "LIB objects para o compilador: $(DEPENDENCIES_OBJECTS)"



# RULES
$(DIRS_BUILD)/startup.o: $(DIRS_STARTUP)/$(STARTUP_FILENAME)
	@echo "Building startup code at $@"
	@mkdir -p $(@D)
	$(TOOLCHAIN_CC) -c $< $(CCFLAGS) -o $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).elf: $(DIRS_SOURCE)/main.cxx $(DIRS_BUILD)/startup.o $(DEPENDENCIES_OBJECTS)
	@echo "Building firmware at $@"
	@mkdir -p $(@D)
	$(TOOLCHAIN_CXX) -o $@  $^ $(LDFLAGS) $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) 

$(DIRS_FIRMWARE)/$(PROJECT_NAME).lst: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "Building $@ ..."
	@$(TOOLCHAIN_OBJDUMP) -S $^ > $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).map: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "Building $2 ..."
	@$(TOOLCHAIN_OBJDUMP) -t $^ > $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).bin: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "Building $@ ..."
	@$(TOOLCHAIN_OBJCOPY) -O binary $< $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).hex: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "Building $@ ..."
	@$(TOOLCHAIN_OBJCOPY) -O ihex $< $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).asm: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "Disassembling to $@ ..."
	@$(TOOLCHAIN_OBJDUMP) -d -C  $< > $@


all: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf $(DIRS_FIRMWARE)/$(PROJECT_NAME).lst $(DIRS_FIRMWARE)/$(PROJECT_NAME).map $(DIRS_FIRMWARE)/$(PROJECT_NAME).bin $(DIRS_FIRMWARE)/$(PROJECT_NAME).hex $(DIRS_FIRMWARE)/$(PROJECT_NAME).asm size

size: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf
	@echo "------------------"
	@echo "FLASH: $(shell $(TOOLCHAIN_OBJSIZE) -d $< | awk '/[0-9]/ {print $$1 + $$2}') bytes"
	@echo "SRAM:  $(shell $(TOOLCHAIN_OBJSIZE) -d $< | awk '/[0-9]/ {print $$2 + $$3}') bytes"
	@echo "------------------"


clean:
	@echo "Cleaning all up ..."
	@rm -rf $(DIRS_FIRMWARE) $(DIRS_BUILD)






