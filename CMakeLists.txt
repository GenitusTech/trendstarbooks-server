cmake_minimum_required(VERSION 3.10)
project(trendstarbooks
    VERSION 1.0.0
    DESCRIPTION "TrendStarBooks - Server"
    HOMEPAGE_URL "https://github.com/GenitusTech/trendstarbooks-server"
    LANGUAGES C
)

# Set C standard with extensions disabled for maximum security
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
