
DIR :=$(LOCAL_DIR)

#STARTUP_OBJS += $(BUILD_DIR)/$(LOCAL_DIR)/startup.o
SRC := $(wildcard $(DIR)/*.c) 
STARTUP_OBJS += $(patsubst $(DIR)/%.c, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))
SRC := $(wildcard $(DIR)/*.cpp) 
STARTUP_OBJS += $(patsubst $(DIR)/%.cpp, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))
SRC := $(wildcard $(DIR)/*.cxx) 
STARTUP_OBJS += $(patsubst $(DIR)/%.cxx, $(BUILD_DIR)/$(DIR)/%.o, $(SRC))


print_startup:
	@echo "LOCAL_DIR = $(DIR)"




$(BUILD_DIR)/$(LOCAL_DIR)/startup.o: $(LOCAL_DIR)/$(STARTUP_SOURCE_FILE).c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.cxx
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@