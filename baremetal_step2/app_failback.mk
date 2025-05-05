# List all source files within LIB_CURRENT_DIR
APP_SOURCES 	:= 	$(wildcard $(APPLICATION_DIR)/*.c)			\
               						$(wildcard $(APPLICATION_DIR)/*.cpp)		\
			   									$(wildcard $(APPLICATION_DIR)/*.cppm)		\
               						$(wildcard $(APPLICATION_DIR)/*.cxx) 		\
			   									$(wildcard $(APPLICATION_DIR)/*.cxxm)		\


APP_OBJECTS 	:= $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(APP_SOURCES))))



app_print:
	@echo "APP_SOURCES =    $(APP_SOURCES)"
	@echo "APP_OBJECTS =    $(APP_OBJECTS)"

$(BUILD_DIR)/$(APPLICATION_DIR)/%.o : $(APPLICATION_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(APPLICATION_DIR) -c $< -o $@

$(BUILD_DIR)/$(APPLICATION_DIR)/%.o : $(APPLICATION_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(APPLICATION_DIR) -c $< -o $@

$(BUILD_DIR)/$(APPLICATION_DIR)/%.o : $(APPLICATION_DIR)/%.cxx
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(APPLICATION_DIR) -c $< -o $@

$(BUILD_DIR)/$(APPLICATION_DIR)/%.o : $(APPLICATION_DIR)/%.cppm
	@mkdir -p $(@D) 
	$(CXX) $(CXXFLAGS) -I$(APPLICATION_DIR) -c $< -o $@

$(BUILD_DIR)/$(APPLICATION_DIR)/%.o : $(APPLICATION_DIR)/%.cxxm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(APPLICATION_DIR) -c $< -o $@
 


	

