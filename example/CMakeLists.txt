option(USE_INSTALLED_CDLL "Use installed library" OFF)

add_executable(example1 example1.c)
add_executable(example2 example2.c)

if (USE_INSTALLED_CDLL)
    find_package(cdll REQUIRED CONFIG)
endif ()

target_link_libraries(example1 PRIVATE cdll)
target_link_libraries(example2 PRIVATE cdll)
