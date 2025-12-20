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

add_subdirectory(src)
