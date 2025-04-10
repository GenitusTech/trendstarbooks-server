cmake_minimum_required(VERSION 3.15...4.0.0)

project(
  trendstarbooks
	VERSION 1.0.0
	DESCRIPTION "TrendStarBooks - Server"
	HOMEPAGE_URL "https://github.com/GenitusTech/trendstarbooks-server"
	LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCE_DIR src)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.h")
