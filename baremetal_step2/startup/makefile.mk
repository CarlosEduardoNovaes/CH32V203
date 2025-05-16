

print_startup:
	@echo "LOCAL_DIR = $(DIR)"


$(BUILD_DIR)/$(STARTUP_DIR)/startup.o: $(STARTUP_DIR)/$(STARTUP_FILENAME)
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -o $@


