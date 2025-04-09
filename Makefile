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

# Compiler flags
CFLAGS := \
	-std=c17 \
	-fstack-protector-strong \
	-fstack-clash-protection \
	-fcf-protection=full \
	-D_FORTIFY_SOURCE=3 \
	-fPIE \
	-fPIC \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wconversion \
	-Wformat=2 \
	-Wformat-security \
	-Wnull-dereference \
	-Wstack-protector \
	-Wstrict-overflow \
	-Wstrict-prototypes \
	-Wwrite-strings \
	-Warray-bounds=2 \
	-Wcast-align \
	-Wcast-qual \
	-Wdouble-promotion \
	-Wduplicated-branches \
	-Wduplicated-cond \
	-Wfloat-equal \
	-Wshadow \
	-Wundef \
	-Wunused \
	-Wlogical-op \
	-Wpointer-arith \
	-Wredundant-decls \
	-O2 \
	-g3 \
	-fno-omit-frame-pointer \
	-fno-common \
	-fno-plt \
	-fvisibility=hidden

	# -Wbad-function-cast
	# -Wmissing-prototypes
	# -D_GLIBCXX_ASSERTIONS
	# -Wno-unused-function
	# -Wno-unused-variable
	# -fsanitize=address
	# -fsanitize=address
	# -fsanitize=undefined
	# -fsanitize=leak
	# -fsanitize-address-use-after-scope

LIBS := \
	-lmariadb

# Linker flags
LDFLAGS := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,-z,noexecstack \
	-Wl,-z,defs \
	-Wl,--as-needed \
	-Wl,--no-undefined \
	-pie \

# Source files
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Includes files
INCLUDES := \
	-I./$(SRC_DIR) \
	-I./$(SRC_DIR)/controller \
	-I./$(SRC_DIR)/model \
	-I./$(SRC_DIR)/router \
	-I./$(SRC_DIR)/utils \
	-I./$(SRC_DIR)/view

# Object files
OBJS := $(SRC_FILES:.c=.o)

# Executable name
EXEC := trendstarbooks

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -n "=== GENERATE *.o - START ===\n"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -n "=== GENERATE *.o - END ===\n"

all: $(EXEC)

$(EXEC): $(OBJS)
	@echo -n "=== BUILD BINARY FILE - START ===\n"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ $(LDFLAGS)
	@echo -n "=== BUILD BINARY FILE - END ===\n"

analyze: \
	analyze-splint \
	analyze-clang \
	analyze-cppcheck \
	analyze-flawfinder

run: $(EXEC)
	@echo -n "=== EXECUTE BINARY - START ===\n"
	./$(EXEC)
	@echo -n "=== EXECUTE BINARY - END ===\n"

clean:
	@echo -n "=== CLEANING - START ===\n"
	@rm -vrf $(ANALYSIS_DIR) $(OBJS) $(EXEC)
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
	@$(CPPCHECK) --enable=all --inconclusive --check-config --std=c17 $(INCLUDES) $(SRC_DIR) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"

$(ANALYSIS_DIR)/report_flawfinder.txt: $(SRC_FILES)
	@echo -n "Running flawfinder analysis...\n"
	@$(FLAWFINDER) --quiet --html --dataonly $(SRC_DIR) > $@ 2>&1 || true
	@echo -n "Analysis report generated at $@\n"
