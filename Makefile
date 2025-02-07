export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

CC      := gcc
CFLAGS  := -Wall -Wextra -I./src
AR      := ar
ARFLAGS := rcs

SRC_DIR   := src
BUILD_DIR := build
TEST_DIR  := test

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
STATIC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
SHARED_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.shared.o, $(SRC_FILES))

# Determine OS to set dynamic library file name
ifeq ($(OS),Windows_NT)
    SHARED_LIB = bb101.dll
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LIB = libbb101.dylib
    else
        SHARED_LIB = libbb101.so
    endif
endif

LIB = libbb101.a

# Default target builds both static and dynamic libraries.
all: static dynamic

# Create build directory if needed.
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Static Library Build ---
# Compile source files to object files (for static library).
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Archive object files into a static library.
static: $(LIB)
$(LIB): $(STATIC_OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

# --- Dynamic Library Build ---
# Compile source files to PIC object files.
$(BUILD_DIR)/%.shared.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Link the shared object files into a dynamic library.
dynamic: $(SHARED_LIB)
$(SHARED_LIB): $(SHARED_OBJ_FILES)
	$(CC) -shared -o $@ $^

# --- Test Target ---
# Build and run the test executable using the dynamic library.
test: dynamic
	$(CC) $(CFLAGS) $(TEST_DIR)/ejemplo.c -L. -lbb101 -o test_library
	./test_library

# --- Clean ---
clean:
	rm -rf $(BUILD_DIR) $(LIB) $(SHARED_LIB) test_my_library

.PHONY: all static dynamic test clean
