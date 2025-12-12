cmake_minimum_required(VERSION 3.28)

project(
        cdll
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "Library for creating generic circular doubly linked lists"
        HOMEPAGE_URL "https://github.com/suyash-purwar/cdll-lib"
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(BUILD_SHARED_LIB "Build shared library" ON)
option(BUILD_STATIC_LIB "Build static library" OFF)

if (BUILD_STATIC_LIB)
    add_library(cdll STATIC src/cdll.c)
endif()

if (BUILD_SHARED_LIB)
    add_library(cdll SHARED src/cdll.c)
endif()

target_include_directories(cdll PUBLIC includes)
target_compile_options(cdll PRIVATE -Wall -Wextra -Wpedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(cdll PRIVATE -Werror -fsanitize=address -fsanitize=undefined)
endif()
