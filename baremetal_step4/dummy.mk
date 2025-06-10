# dummy.mk – regras padrão para bibliotecas

# Use LIB_CURRENT_DIR como prefixo (ela deve ser definida antes de incluir este arquivo)
LIB_NAME    := $(notdir $(LIB_CURRENT_DIR))
LIB_NAME    := $(LIB_CURRENT_DIR)
LIB_OBJECTS := $(patsubst %.c,%.o,$(wildcard $(LIB_CURRENT_DIR)/*.c)) 		\
               $(patsubst %.cpp,%.o,$(wildcard $(LIB_CURRENT_DIR)/*.cpp)) 	\
			   $(patsubst %.cppm,%.o,$(wildcard $(LIB_CURRENT_DIR)/*.cppm)) \
               $(patsubst %.cxx,%.o,$(wildcard $(LIB_CURRENT_DIR)/*.cxx)) 	\
			   $(patsubst %.cxxm,%.o,$(wildcard $(LIB_CURRENT_DIR)/*.cxxm)) \

LIB_TARGET := $(BUILD_DIR)/lib$(LIB_NAME).a

$(LIB_TARGET): $(LIB_OBJECTS)
	@echo "Building $@ ..."
	@echo "Requisitos: $^"
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

LIBRARY_TARGETS += $(LIB_TARGET)
OBJECTS += $(LIB_OBJECTS)
INCLUDE_DIRS += -I$(LIB_CURRENT_DIR)
