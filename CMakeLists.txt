cmake_minimum_required(VERSION 3.28)

project(
        ilist
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "An intrusive circular doubly linked list"
        HOMEPAGE_URL "https://github.com/suyash-purwar/ilist"
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(BUILD_EXAMPLE_APP "Build example application" OFF)
option(BUILD_DOCS "Build docs" OFF)
option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if (BUILD_EXAMPLE_APP)
    add_subdirectory(example)
endif ()

if (BUILD_DOCS)
    add_subdirectory(docs)
endif ()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
