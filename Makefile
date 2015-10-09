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
	rm -rf $(BUILD_DIR) $(TARGET_DIR)
