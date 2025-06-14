# COMPONENT CONFIGURATION
COMPONENT_DEPENDENCIES      := bare
COMPONENT_SOURCE_FILES      := system.cxx

# INFERED VALUES
COMPONENT_NAME              := $(CURRENT_COMPONENT)
COMPONENT_DIRECTORY         := $(CURRENT_COMPONENT_DIRECTORY)
COMPONENT_TARGET            := $(CURRENT_TARGET)
COMPONENT_TARGET_DIRECTORY  := $(CURRENT_TARGET_DIRECTORY)

COMPONENT_OBJECT_FILES :=   $(patsubst %.cpp,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cppm,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cxx,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cxxm,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.c,$(COMPONENT_TARGET_DIRECTORY)/%.o, $(COMPONENT_SOURCE_FILES))))))

COMPONENT_DEPENDENCIES_OBJECTS :=  $(addprefix $(DIRS_BUILD)/$(DIRS_LIBRARIES)/lib, $(addsuffix .a, $(COMPONENT_DEPENDENCIES)))



${COMPONENT_TARGET}: $(COMPONENT_OBJECT_FILES)
	@echo "Joining objects into: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_AR) -rcs  $@ $^

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/src/%.c $(COMPONENT_DEPENDENCIES_OBJECTS)
	@echo "      ... building object: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_CC) $(CCFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/src/%.cpp $(COMPONENT_DEPENDENCIES_OBJECTS)
	@echo "      ... building object: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_CXX) $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/src/%.cxx $(COMPONENT_DEPENDENCIES_OBJECTS)
	@echo "      ... building object: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_CXX) $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/src/%.cppm $(COMPONENT_DEPENDENCIES_OBJECTS)
	@echo "      ... building object: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_CXX) $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -x c++ -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/src/%.cxxm $(COMPONENT_DEPENDENCIES_OBJECTS)
	@echo "      ... building object: $@"
	@mkdir -p $(@D)
	@$(TOOLCHAIN_CXX) $(CXXFLAGS) $(DEPENDENCIES_INCLUDE_DIRS) -x c++ -c $< -o $@
