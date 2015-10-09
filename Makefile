# Simple makefile for a generic C project
#
# This expects a src/main.c file as executable,
# and autodetects any other file under $(SRC_DIR).
#
# It expects those files to have a corresponding `.h` file
#
# Configure:
#  * OVERRIDE_CC: I prefer clang
#  * CC_FLAGS: Flags passed to the c compiler
#  * CC_LINKFLAGS: Flags passed to the linker
#  * EXECUTABLE_NAME: The name of the executable,
#	   which will go inside $(TARGET_DIR)
#  * {TARGET,BUILD,SRC}_DIR: Self-descriptive names

OVERRIDE_CC ?= clang
CC := $(OVERRIDE_CC)
CC_FLAGS := $(CC_FLAGS) -Wall -std=c99 -fPIC
CC_LINKFLAGS := -lm

TARGET_DIR := target
BUILD_DIR := build
SRC_DIR := src
TEST_DIR := tests
LIB := $(TARGET_DIR)/libcollides.a

SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/**/*.c)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/tests/%.o, $(TEST_SOURCES))


.PHONY: all
all: $(LIB)
	@echo > /dev/null

.PHONY: release
release: CC_FLAGS := -O3
release: clean $(LIB)

$(LIB): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: src/%.c src/%.h
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_DIR)/tests/%.o: CC_FLAGS := $(CC_FLAGS) -I src
$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c $(TEST_DIR)/%.h
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

.PHONY: test
test: $(BUILD_DIR)/tests/tests
	@$<

$(BUILD_DIR)/tests/tests: $(TEST_OBJECTS) $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(filter-out $(LIB), $^) -o $@ $(CC_LINKFLAGS) -Ltarget -lcollides

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(TARGET_DIR)
