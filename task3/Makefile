CXX = g++
CXX_FLAGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow -O3 -std=c++17
LD_FLAGS = -static -latomic

# Final binary
BIN = pdc_app
# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

# List of all .cpp source files.
#CPP = $(wildcard src/*.cpp) 
CPP = src/GpioPin.cpp src/main_app.cpp src/US_snsr.cpp src/UI.cpp src/pdc.cpp

# All .o files go to build dir.
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)

usage:
	@echo "usage: make <valid_target>" 
	@echo "valid targets: all, doc, clean"


all: $(BIN)

# Default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@
	@echo "Linking complete!"

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@echo -e "Compiled "$<" successfully!\n"

.PHONY : clean
clean :
	-rm -rf $(BUILD_DIR)

doc :
	doxygen src/docconfig

#debug target
print-%:
	@echo "$*=$($*)"
