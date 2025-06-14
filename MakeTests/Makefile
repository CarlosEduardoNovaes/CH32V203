# PROJECT CONFIGURATION
PROJECT_NAME			          := baremetal
PROJECT_DEPENDENCIES        := pinled registers


# Files and Folders
DIRS_FIRMWARE			          := firmware
DIRS_BUILD                  := build
DIRS_STARTUP     	          := startup
DIRS_LIBRARIES              := libs
DIRS_SOURCE                 := src



# Lista acumulada de dependências (com deduplicação)
ALL_DEPENDENCIES :=

# Função para resolver dependências recursivamente
define scan_dependencies
  $(foreach dep,$(1),\
    $(if $(filter $(dep),$(ALL_DEPENDENCIES)),,\
      $(eval include $(DIRS_LIBRARIES)/$(dep)/makefile.mk) \
      $(eval ALL_DEPENDENCIES += $(dep)) \
      $(call scan_dependencies,$(COMPONENT_DEPENDENCIES)) \
    )\
  )
endef

# Função para estabelecer regras de compilação
define generate_rules
  $(foreach dep,$(1),\
		$(eval CURRENT_COMPONENT := $(dep)) \
		$(eval CURRENT_COMPONENT_DIRECTORY := $(DIRS_LIBRARIES)/$(dep)) \
		$(eval CURRENT_TARGET := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/lib$(dep).a) \
		$(eval CURRENT_TARGET_DIRECTORY := $(DIRS_BUILD)/$(DIRS_LIBRARIES)/$(dep)) \
		$(eval include $(DIRS_LIBRARIES)/$(dep)/makefile.mk) \
		$(eval $(BUILD_COMPONENT_RULES)) \
  )
endef

# Gatilho para resolver as dependências
$(eval $(call scan_dependencies,$(PROJECT_DEPENDENCIES)))

# Geração automática dos diretórios de inclusão
DEPENDENCIES_INCLUDE_DIRS := $(addprefix -Ilibs/, $(addsuffix /include, $(ALL_DEPENDENCIES)))
DEPENDENCIES_LIBRARY_DIRS := $(addprefix -L$(DIRS_BUILD)/libs/, $(ALL_DEPENDENCIES))
DEPENDENCIES_LIBRARY_FLAGS := $(addprefix -l, $(ALL_DEPENDENCIES))
DEPENDENCIES_OBJECTS := $(addprefix $(DIRS_BUILD)/libs/lib, $(addsuffix .a, $(ALL_DEPENDENCIES)))

# Gatilho para gerar regras
$(eval $(call generate_rules,$(ALL_DEPENDENCIES)))

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

$(DIRS_FIRMWARE)/$(PROJECT_NAME).elf: $(DIRS_SOURCE)/main.cxx $(DIRS_BUILD)/startup.o
	@echo "Building firmware..."
	@mkdir -p $(@D)
	$(TOOLCHAIN_CC) -c $< $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -o $@
	$(TOOLCHAIN_CC) -o $@ $^ $(LDFLAGS)

all: $(DIRS_FIRMWARE)/$(PROJECT_NAME).elf






