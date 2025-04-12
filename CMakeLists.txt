cmake_minimum_required(VERSION 3.25.1...4.0.0)

project(
  trendstarbooks
  VERSION 1.0.0
  DESCRIPTION "TrendStarBooks - Server"
  HOMEPAGE_URL "https://github.com/GenitusTech/trendstarbooks-server"
  LANGUAGES C)

cmake_policy(SET CMP0076 NEW) # Use absolute install paths
cmake_policy(SET CMP0077 NEW) # Honor explicit option() commands
cmake_policy(SET CMP0135 NEW) # Properly handle file(GENERATE) permission

option(SERVER_ENABLE_HARDENING "Enable all security hardening features" ON)
option(SERVER_ENABLE_WARNINGS "Enable extensive compiler warnings" ON)
option(SERVER_ENABLE_LTO "Enable link-time optimization for security" ON)
option(SERVER_ENABLE_FORTIFY "Enable runtime buffer overflow checks" ON)
option(SERVER_ENABLE_RELRO "Enable RELRO protection" ON)
option(SERVER_ENABLE_PIE "Enable Position Independent Executable" ON)
option(SERVER_ENABLE_STACK_PROTECTION "Enable stack protection" ON)
option(SERVER_ENABLE_ASAN "Enable Address Sanitizer" OFF)
option(SERVER_ENABLE_UBSAN "Enable Undefined Behavior Sanitizer" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SRC_DIR src)
file(GLOB_RECURSE SERVER_SOURCE_FILES "${SRC_DIR}/*.c")
file(GLOB_RECURSE SERVER_HEADER_FILES "${SRC_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SERVER_SOURCE_FILES} ${SERVER_HEADER_FILES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/${SRC_DIR}
          ${PROJECT_SOURCE_DIR}/${SRC_DIR}/controller
          ${PROJECT_SOURCE_DIR}/${SRC_DIR}/model
          ${PROJECT_SOURCE_DIR}/${SRC_DIR}/router
          ${PROJECT_SOURCE_DIR}/${SRC_DIR}/utils
          ${PROJECT_SOURCE_DIR}/${SRC_DIR}/view)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Threads::Threads
)

if(SERVER_ENABLE_HARDENING)
  add_compile_options(
    -D_POSIX_C_SOURCE=200809L
    -fstack-protector-strong # Stack protection
    -fPIE
    -fPIC # Position Independent Executable/Code
    -D_FORTIFY_SOURCE=2 # Runtime buffer overflow checks
    -O2 # Optimizations (balance speed/security
  )
  add_link_options(
    -Wl,-z,now # Disable lazy binding
    -Wl,-z,relro # Read-only relocations
    -Wl,-z,noexecstack
    -Wl,-z,defs
    -Wl,--as-needed
    -Wl,--no-undefined
    -pie # ASLR support
  )
endif()

if(SERVER_ENABLE_WARNINGS)
  add_compile_options(
    -Wall
    -Warray-bounds=2
    -Wbad-function-cast
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wdeprecated
    -Wdouble-promotion
    -Wduplicated-cond
    -Wduplicated-branches
    -Werror
    -Wextra
    -Wfloat-equal
    -Wformat=2
    -Wformat-security
    -Wlogical-op
    -Wmissing-prototypes
    -Wno-unused-function
    -Wno-unused-variable
    -Wnull-dereference
    -Wpedantic
    -Wpointer-arith
    -Wredundant-decls
    -Wshadow
    -Wsign-conversion
    -Wstack-protector
    -Wstrict-overflow
    -Wstrict-prototypes
    -Wundef
    -Wunused
    -Wwrite-strings)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(
    -fsanitize=address,undefined,leak #
    -fsanitize-address-use-after-scope #
    -fno-omit-frame-pointer #
  )
  add_link_options(-fsanitize=address,undefined,leak)
endif()

# message(">>>x ${CMAKE_BUILD_TYPE}") # Security hardening flags
# add_compile_options( -Wall -Wextra -Wpedantic # Strict warnings
# -Werror=implicit-function-declaration # Catch missing declarations
# -fstack-protector-strong           # Stack protection -fPIE -fPIC # Position
# Independent Executable/Code -D_FORTIFY_SOURCE=2               # Runtime buffer
# overflow checks -O2                               # Optimizations (balance
# speed/security) )

# # Secure compilation flags target_compile_options(${PROJECT_NAME} PRIVATE #
# Security hardening -fstack-protector-strong -fstack-clash-protection
# -fcf-protection=full -D_FORTIFY_SOURCE=3 -fPIE -fPIC -Wall -Wextra -Wpedantic
# -Werror -Wconversion -Wformat=2 -Wformat-security -Wnull-dereference
# -Wstack-protector -Wstrict-overflow -Wstrict-prototypes -Wwrite-strings
# -Warray-bounds=2 -Wcast-align -Wcast-qual -Wdouble-promotion
# -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow -Wundef
# -Wunused -Wlogical-op -Wpointer-arith -Wredundant-decls

# # Optimization and debugging -O2  # Balance between performance and security
# -g3  # Debug symbols -fno-omit-frame-pointer

# # Additional security -fno-common -fno-plt -fvisibility=hidden )
