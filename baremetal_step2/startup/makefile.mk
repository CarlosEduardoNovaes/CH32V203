


DIR :=$(LOCAL_DIR)
print_startup:
	@echo "LOCAL_DIR = $(DIR)"

STARTUP_OBJS += $(BUILD_DIR)/$(LOCAL_DIR)/startup.o


$(BUILD_DIR)/$(LOCAL_DIR)/startup.o: $(LOCAL_DIR)/$(STARTUP_SOURCE_FILE).c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LOCAL_DIR)/%.o: $(LOCAL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@