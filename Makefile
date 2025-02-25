CC      := gcc
CFLAGS  := -Wall -Wextra -I./src
AR      := ar
ARFLAGS := rcs

SRC_DIR     := src
BUILD_DIR   := build
TEST_DIR    := test
LIB_DIR     := lib
RELEASE_DIR := releases

SRC_FILES        := $(wildcard $(SRC_DIR)/*.c)
HEADERS          := $(wildcard $(SRC_DIR)/*.h)
STATIC_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
SHARED_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.shared.o, $(SRC_FILES))

STATIC_LIB = lib/libbb101.a

ifeq ($(OS),Windows_NT)
    SHARED_LIB = lib/libbb101.dll
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LIB = lib/libbb101.dylib
    else
        SHARED_LIB = lib/libbb101.so
    endif
endif

init: 
	mkdir $(BUILD_DIR)
	mkdir $(LIB_DIR)
	mkdir $(RELEASE_DIR)

# --- Construcción de la Librería Estática ---
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

static: init $(BUILD_DIR) $(STATIC_LIB)
$(STATIC_LIB): $(STATIC_OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

# --- Construcción de la Librería Dinámica ---
$(BUILD_DIR)/%.shared.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

dynamic: $(BUILD_DIR) $(SHARED_LIB)
$(SHARED_LIB): $(SHARED_OBJ_FILES)
	$(CC) -shared -o $@ $^

install-headers:
ifeq ($(OS),Windows_NT)
	@echo "Headers"
else
	install -m 644 $(SRC_DIR)/bb101.h /usr/local/include
endif

install: clean init static dynamic install-headers
ifeq ($(OS),Windows_NT)
	copy $(SHARED_LIB) C:\Windows\System32
else
	install -m 755 $(SHARED_LIB) /usr/local/lib
	ldconfig
endif

uninstall:
ifeq ($(OS),Windows_NT)
	del C:\Windows\System32\bb101.dll
else
	rm -f /usr/local/lib/libbb101.dylib
	rm -f /usr/local/lib/libbb101.so
	rm -f /usr/local/include/bb101.h
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q $(LIB_DIR)
else
	rm -rf $(BUILD_DIR) $(SHARED_LIB) $(LIB_DIR) $(RELEASE_DIR) test_library
endif
