DIR :=$(LOCAL_DIR)

# CXX = g++
# CXXFLAGS = -std=c++20 -fmodules-ts 

# # Rule for compiling module interface units (.cppm)
# %.pcm: %.cppm
# 	$(CXX) $(CXXFLAGS) --precompile $< -o $@

# # Rule for compiling source files (.cpp)
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Rule for linking the executable
# main: main.o my_module.pcm # Replace my_module with your module name
# 	$(CXX) $(CXXFLAGS) main.o -o main

# # Clean rule
# clean:
# 	rm -f *.o *.pcm main

HARDWARE_OBJS += $(BUILD_DIR)/$(LOCAL_DIR)/hw.o

print_hw:
	@echo "LOCAL_DIR = $(DIR)"