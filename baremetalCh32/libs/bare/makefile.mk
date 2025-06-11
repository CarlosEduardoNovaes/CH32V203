COMPONENT_DEPENDENCIES := 
COMPONENT_SOURCE_FILES :=  bare-traits.cppm bare.cppm


COMPONENT_NAME := $(CURRENT_COMPONENT)
COMPONENT_DIRECTORY := $(CURRENT_COMPONENT_DIRECTORY)
COMPONENT_TARGET := $(CURRENT_TARGET)
COMPONENT_TARGET_DIRECTORY := $(CURRENT_TARGET_DIRECTORY)

COMPONENT_OBJECT_FILES :=   $(patsubst %.cpp,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cppm,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cxx,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.cxxm,$(COMPONENT_TARGET_DIRECTORY)/%.o, \
                            $(patsubst %.c,$(COMPONENT_TARGET_DIRECTORY)/%.o, $(COMPONENT_SOURCE_FILES))))))


${COMPONENT_TARGET}: $(COMPONENT_OBJECT_FILES)
	@echo "Building: $@"
	@echo "prerequisites: $^"
	@mkdir -p $(@D)
	$(TOOLCHAIN_AR) -rcs  $@ $^

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/%.c
	@mkdir -p $(@D)
	$(TOOLCHAIN_CC) $(CCFLAGS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/%.cpp
	@mkdir -p $(@D)
	$(TOOLCHAIN_CXX) $(CXXFLAGS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/%.cxx
	@mkdir -p $(@D)
	$(TOOLCHAIN_CXX) $(CXXFLAGS) -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/%.cppm
	@mkdir -p $(@D) 
	$(TOOLCHAIN_CXX) $(CXXFLAGS) -x c++ -c $< -o $@

$(COMPONENT_TARGET_DIRECTORY)/%.o : $(COMPONENT_DIRECTORY)/%.cxxm
	@mkdir -p $(@D)
	$(TOOLCHAIN_CXX) $(CXXFLAGS) -x c++ -c $< -o $@