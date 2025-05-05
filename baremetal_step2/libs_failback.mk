
LIB_NAME    := $(notdir $(LIB_CURRENT_DIR))



# List all source files within LIB_CURRENT_DIR
CURRENT_LIB_SOURCES 	:= 	$(wildcard $(LIB_CURRENT_DIR)/*.c)			\
               						$(wildcard $(LIB_CURRENT_DIR)/*.cpp)		\
			   									$(wildcard $(LIB_CURRENT_DIR)/*.cppm)		\
               						$(wildcard $(LIB_CURRENT_DIR)/*.cxx) 		\
			   									$(wildcard $(LIB_CURRENT_DIR)/*.cxxm)		\


CURRENT_LIB_OBJECTS 	:= $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(CURRENT_LIB_SOURCES))))




$(BUILD_DIR)/$(LIBRARY_DIR)/$(LIB_CURRENT_NAME)/%.o : $(LIB_CURRENT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIBRARY_DIR)/$(LIB_CURRENT_NAME)/%.o : $(LIB_CURRENT_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIBRARY_DIR)/$(LIB_CURRENT_NAME)/%.o : $(LIB_CURRENT_DIR)/%.cxx
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIBRARY_DIR)/$(LIB_CURRENT_NAME)/%.o : $(LIB_CURRENT_DIR)/%.cppm
	@mkdir -p $(@D) 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIBRARY_DIR)/$(LIB_CURRENT_NAME)/%.o : $(LIB_CURRENT_DIR)/%.cxxm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
 

$(BUILD_DIR)/$(LIBRARY_DIR)/lib$(LIB_CURRENT_NAME).a: $(CURRENT_LIB_OBJECTS)
	@echo "Building $@ with generic rules for libs ..."
	@mkdir -p $(@D)
	$(AR) rcs $@ $^
	

