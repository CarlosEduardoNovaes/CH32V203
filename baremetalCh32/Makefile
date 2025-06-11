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

# PROJECT CONFIGURATION
PROJECT_NAME			    := baremetal
PROJECT_DEPENDENCIES        := system

# Microcontroller Settings
CPU_MODEL					:= CH32V203x6
F_CPU   					:= 144000000
LDSCRIPT 					:= ch32v203x6.ld
CPUARCH  					:= -march=rv32imac -mabi=ilp32
STARTUP_FILENAME			:= startup_ch32v203.c

# Files and Folders
DIRS_FIRMWARE			    := firmware
DIRS_BUILD                  := build
DIRS_STARTUP     	        := startup
DIRS_LIBRARIES              := libs
DIRS_SOURCE                 := src


# Compiler Flags
CCFLAGS_OPTIMIZATION 	= -O3 -ffunction-sections -fdata-sections -fno-builtin -flto
CCFLAGS_DEBUG	 				= -g
CCFLAGS_ARCHITECTURE  = $(CPUARCH) 
CCFLAGS_DEFINES      	= -DF_CPU=$(F_CPU)
CCFLAGS_GENERAL       = -Wall
CCFLAGS_INCLUDES      = -I$(NEWLIB) -I$(LIBRARY_DIR) -I$(APPLICATION_DIR)


CCFLAGS     =  $(CCFLAGS_DEBUG) $(CCFLAGS_OPTIMIZATION)  -L$(BUILD_DIR)/$(LIBRARY_DIR) -nostdlib
CCFLAGS     += $(CCFLAGS_ARCHITECTURE) $(CCFLAGS_DEFINES) $(CCFLAGS_GENERAL) $(CCFLAGS_INCLUDES) 
CXXFLAGS    = $(CFLAGS) -fno-exceptions -fno-rtti -std=c++20 -fmodules-ts '-fmodule-mapper=|@g++-mapper-server -r'$(DIRS_BUILD)/gcm.cache  
LDFLAGS  	  = -T$(STARTUP_DIR)/$(LDSCRIPT) -lgcc -Wl,--gc-sections,--build-id=none




# Lista acumulada de dependências (com deduplicação)
ALL_DEPENDENCIES :=

# Função para resolver dependências recursivamente
define resolve_dependencies
  $(foreach dep,$(1),\
    $(if $(filter $(dep),$(ALL_DEPENDENCIES)),,\
	  $(eval CURRENT_COMPONENT := $(dep)) \
	  $(eval CURRENT_COMPONENT_DIRECTORY := $(DIRS_LIBRARIES)/$(dep)) \
	  $(eval CURRENT_TARGET := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/lib$(dep).a) \
	  $(eval CURRENT_TARGET_DIRECTORY := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/$(dep)) \
      $(eval include $(DIRS_LIBRARIES)/$(dep)/makefile.mk) \
      $(eval ALL_DEPENDENCIES += $(dep)) \
      $(call resolve_dependencies,$(COMPONENT_DEPENDENCIES)) \
    )\
  )
endef

# Gatilho para resolver as dependências
$(eval $(call resolve_dependencies,$(PROJECT_DEPENDENCIES)))

# Geração automática dos diretórios de inclusão
DEPENDENCIES_INCLUDE_DIRS := $(addprefix -Ilibs/, $(addsuffix /include, $(ALL_DEPENDENCIES)))
DEPENDENCIES_LIBRARY_DIRS := $(addprefix -L$(DIRS_BUILD)/libs/, $(ALL_DEPENDENCIES))
DEPENDENCIES_LIBRARY_FLAGS := $(addprefix -l, $(ALL_DEPENDENCIES))
DEPENDENCIES_OBJECTS := $(addprefix $(DIRS_BUILD)/libs/lib, $(addsuffix .a, $(ALL_DEPENDENCIES)))

# Exemplo de uso
print:
	@echo "Projeto usa: $(PROJECT_DEPENDENCIES)"
	@echo "Tudo que será incluído: $(ALL_DEPENDENCIES)"
	@echo "Includes para o compilador: $(DEPENDENCIES_INCLUDE_DIRS)"
	@echo "LIB DIRS para o compilador: $(DEPENDENCIES_LIBRARY_DIRS)"
	@echo "LIB flags para o compilador: $(DEPENDENCIES_LIBRARY_FLAGS)"
	@echo "LIB objects para o compilador: $(DEPENDENCIES_OBJECTS)"



# RULES
$(DIRS_BUILD)/startup.o: $(DIRS_STARTUP)/$(STARTUP_FILENAME)
	@echo "Building startup code..."
	@mkdir -p $(@D)
	$(TOOLCHAIN_CC) -c $< $(CCFLAGS) -o $@

$(DIRS_FIRMWARE)/$(PROJECT_NAME).elf: $(DIRS_SOURCE)/main.c $(DIRS_BUILD)/$(DIRS_STARTUP)/startup.o 
	@echo "Building firmware..."
	@mkdir -p $(@D)
	$(TOOLCHAIN_CC) -c $< $(CCFLAGS) -o $@
	$(TOOLCHAIN_CC) -o $@ $^ $(LDFLAGS)







