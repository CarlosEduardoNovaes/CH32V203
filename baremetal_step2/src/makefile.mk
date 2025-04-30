DIR :=$(LOCAL_DIR)

SRC := $(wildcard $(DIR)/*.c) 
APPLICATION_OBJS += $(patsubst $(DIR)/%.c, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))
SRC := $(wildcard $(DIR)/*.cpp) 
APPLICATION_OBJS += $(patsubst $(DIR)/%.cpp, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))
SRC := $(wildcard $(DIR)/*.cxx) 
APPLICATION_OBJS += $(patsubst $(DIR)/%.cxx, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))


print_src:
	@echo "LOCAL_DIR = $(DIR)"

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
