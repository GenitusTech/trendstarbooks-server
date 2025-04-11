# GCC (v.12)
CC := gcc-12

## Tools
# SPLINT (v.3)
SPLINT := splint
# CLANG (v.19)
CLANG := clang-19
# CPPCHECK (v.2)
CPPCHECK := cppcheck
# FLAWFINDER (v.2)
FLAWFINDER := flawfinder

ANALYSIS_DIR := analysis

SRC_DIR := src

# Source files
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
# Object files
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))
# Executable name
EXEC := trendstarbooks

LIBS := \
	-lpthread \
	-lmariadb

WARNINGS := \
	-Wall \
	-Warray-bounds=2 \
	-Wbad-function-cast \
	-Wcast-align \
	-Wcast-qual \
	-Wconversion \
	-Wdeprecated \
	-Wdouble-promotion \
	-Wduplicated-cond \
	-Wduplicated-branches \
	-Werror \
	-Wextra \
	-Wfloat-equal \
	-Wformat=2 \
	-Wformat-security \
	-Wlogical-op \
	-Wmissing-prototypes \
	-Wno-unused-function \
	-Wno-unused-variable \
	-Wnull-dereference \
	-Wpedantic \
	-Wpointer-arith \
	-Wredundant-decls \
	-Wshadow \
	-Wsign-conversion \
	-Wstack-protector \
	-Wstrict-overflow \
	-Wstrict-prototypes \
	-Wundef \
	-Wunused \
	-Wwrite-strings \

# Compiler flags
CFLAGS := $(WARNINGS) \
	-std=c17 \
	-D_FORTIFY_SOURCE=2 \
	-D_GLIBCXX_ASSERTIONS \
	-O2 \
	-g3 \
	-fstack-clash-protection \
	-fstack-protector-strong \
	-fPIE \
	-fPIC \
	-fcf-protection=full \
	-fno-common \
	-fno-plt \
	-fsanitize=address,undefined,leak \
	-fsanitize-address-use-after-scope \
	-fno-omit-frame-pointer \
	-fvisibility=hidden

# Linker flags
LDFLAGS := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,-z,noexecstack \
	-Wl,-z,defs \
	-Wl,--as-needed \
	-Wl,--no-undefined \
	-pie

# Include Directories
INCLUDE := \
	-I./$(SRC_DIR) \
	-I./$(SRC_DIR)/controller \
	-I./$(SRC_DIR)/model \
	-I./$(SRC_DIR)/router \
	-I./$(SRC_DIR)/utils \
	-I./$(SRC_DIR)/view

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(INCLUDE) -c $< -o $@

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	@echo -n "\n=== BUILD BINARY FILE - START ===\n"
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(INCLUDE) $(OBJ_FILES) -o $@
	@echo -n "=== BUILD BINARY FILE - END ===\n"

analyze: \
	analyze-splint \
	analyze-clang \
	analyze-cppcheck \
	analyze-flawfinder

run: $(EXEC) analyze
	@echo -n "=== EXECUTE BINARY - START ===\n\n"
	./$(EXEC)
	@echo -n "\n\n=== EXECUTE BINARY - END ===\n"

clean:
	@echo -n "=== CLEANING - START ===\n"
	@rm -vrf $(ANALYSIS_DIR) $(OBJ_FILES) $(EXEC)
	@echo -n "=== CLEANING - END ===\n"

.PHONY: all analyze run clean

$(ANALYSIS_DIR):
	$(shell mkdir -p $(ANALYSIS_DIR))

analyze-splint: $(ANALYSIS_DIR) $(ANALYSIS_DIR)/report_splint.txt
analyze-clang: $(ANALYSIS_DIR) $(ANALYSIS_DIR)/report_clang.txt
analyze-cppcheck: $(ANALYSIS_DIR) $(ANALYSIS_DIR)/report_cppcheck.txt
analyze-flawfinder: $(ANALYSIS_DIR) $(ANALYSIS_DIR)/report_flawfinder.txt

$(ANALYSIS_DIR)/report_splint.txt: $(SRC_FILES)
	@echo -n "Running splint analysis...\n"
	@$(SPLINT) $(SRC_FILES) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"

$(ANALYSIS_DIR)/report_clang.txt: $(SRC_FILES)
	@echo -n "Running clang analysis...\n"
	@$(CLANG) --analyze $(CFLAGS) $(SRC_FILES) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"

$(ANALYSIS_DIR)/report_cppcheck.txt: $(SRC_FILES)
	@echo -n "Running cppcheck analysis...\n"
	@$(CPPCHECK) \
		--suppress=missingIncludeystem \
		--enable=all --inconclusive --check-config --std=c17 \
		$(INCLUDE) $(SRC_DIR) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"

$(ANALYSIS_DIR)/report_flawfinder.txt: $(SRC_FILES)
	@echo -n "Running flawfinder analysis...\n"
	@$(FLAWFINDER) --quiet --html --dataonly $(SRC_DIR) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"
