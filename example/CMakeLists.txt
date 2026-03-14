option(USE_INSTALLED_ILIST "Use installed library" OFF)

add_executable(example1 example1.c)
add_executable(example2 example2.c)

if (USE_INSTALLED_ILIST)
    find_package(ilist REQUIRED CONFIG)
endif ()

target_link_libraries(example1 PRIVATE ilist)
target_link_libraries(example2 PRIVATE ilist)
