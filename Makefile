## Compilation Tool: GCC (v.12)
CC := gcc-12

## Debug Tools: splint clang cppcheck flawfinder
# SPLINT (v.3)
SPLINT := splint
# CLANG (v.19)
CLANG := clang-19
# CPPCHECK (v.2)
CPPCHECK := cppcheck
# FLAWFINDER (v.2)
FLAWFINDER := flawfinder

# Analysis Directory
ANALYSIS_DIR := analysis

SRC_DIR := src

# Executable name
TARGET := trendstarbooks
# Source files
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
# Object files
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))

# Standard Compliance & Strictness
CFLAGS += -std=c99# Enforces strict C99 compliance
CFLAGS += -pedantic# Rejects non-standard GNU extensions

# Enables Warning Flags (Catch Potential Bugs)
CFLAGS += -Wall -Wextra# Basic warnings (unused vars, implicit conversions, etc.)
CFLAGS += -Werror# Treats all warnings as errors (strict mode)
CFLAGS += -Wpedantic# Strict ISO C compliance
CFLAGS += -Wformat=2# Checks printf/scanf format strings
CFLAGS += -Wformat-overflow=2# Informs about printf/scanf format strings that may cause buffer overflows
CFLAGS += -Wformat-truncation=2# Informs about snprintf truncation risks
CFLAGS += -Wconversion# Informs about implicit type conversions
CFLAGS += -Wstrict-overflow=4# Informs about potential signed overflow
CFLAGS += -Warray-bounds=2# Strict bounds-checking for arrays
CFLAGS += -Wnull-dereference# Informs about possible null pointer dereferences
CFLAGS += -Wduplicated-cond# Informs about duplicated conditions in if-else chains
CFLAGS += -Wduplicated-branches# Informs if two branches in if-else are identical
CFLAGS += -Wlogical-op# Informs about suspicious uses of logical operators
CFLAGS += -Wrestrict# Informs when a restricted pointer (restrict) is incorrectly used
CFLAGS += -Wshadow# Informs if a variable shadows another
CFLAGS += -Wjump-misses-init# Informs if a goto skips variable initialization
CFLAGS += -Wdouble-promotion# Informs when float is implicitly promoted to double
CFLAGS += -Wmisleading-indentation# Informs about indentation that doesn’t match control flow
CFLAGS += -Wmissing-prototypes# Ensures functions have prototypes
CFLAGS += -Wstrict-prototypes# Rejects int foo() in favor of int foo(void)

# Memory & Control-Flow Protection
CFLAGS += -fstack-protector-strong# Protects against stack smashing
CFLAGS += -fstack-clash-protection# Prevents stack clash attacks (interleaving stack/heap memory)
CFLAGS += -fno-common# Places uninitialized globals in BSS instead of "common" section
CFLAGS += -fvisibility=hidden# Hides symbols by default unless explicitly exported

# Linker Flags (Security Hardening)
LDFLAGS += -Wl,-z,now# Disables lazy binding (prevents GOT overwrite attacks)
LDFLAGS += -Wl,-z,relro# Makes the GOT read-only after relocation
LDFLAGS += -Wl,-z,noexecstack# Non-executable stack (NX bit)
LDFLAGS += -Wl,-z,defs# Ensures no undefined symbols exist in the final binary
LDFLAGS += -Wl,--as-needed# Links only libraries that are actually used (reduces bloat)
LDFLAGS += -Wl,--no-undefined# Rejects linking if undefined symbols remain (strict mode)

ifeq ($(origin BUILD), undefined)
BUILD = debug
endif

ifeq ($(BUILD),production)
# Security & Hardening Flags
CFLAGS += -O2# Optimizes for performance (enables D_FORTIFY_SOURCE)
CFLAGS += -D_FORTIFY_SOURCE=3# untime buffer overflow checks (requires -O2)
CFLAGS += -flto#
CFLAGS += -fPIE# Position-Independent Executable (ASLR hardening)
CFLAGS += -fPIC# Position-Independent Code (ASLR friendly)
CFLAGS += -fcf-protection=full# Control-Flow Integrity (CPU-based protection against ROP/jump-oriented attacks)
CFLAGS += -fno-plt# Avoids the PLT (Procedure Linkage Table) for faster, more secure dynamic linking

LDFLAGS += -pie# ASLR-enabled executable
endif

ifeq ($(BUILD),debug)
CFLAGS += -Og#
CFLAGS += -g3# Adds debug symbols (useful for gdb)
CFLAGS += -fsanitize=undefined -fsanitize=address -fsanitize=leak
CFLAGS += -fsanitize-address-use-after-scope
CFLAGS += -fno-omit-frame-pointer# Keeps frame pointers for better debugging/stack traces

LDFLAGS += -fsanitize=undefined -fsanitize=address -fsanitize=leak
endif

# Include Directories
INCLUDE := \
	-I./$(SRC_DIR) \
	-I./$(SRC_DIR)/controller \
	-I./$(SRC_DIR)/middleware \
	-I./$(SRC_DIR)/model \
	-I./$(SRC_DIR)/utils \
	-I./$(SRC_DIR)/view

LIBS = -lpthread

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(LIBS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -frv $(OBJ_FILES) $(TARGET)

.PHONY: all clean debug production

debug:
	@$(MAKE) BUILD=debug

production:
	@$(MAKE) BUILD=production
