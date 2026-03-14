include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(ilist SHARED ilist.c)

target_include_directories(
        ilist PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(ilist PUBLIC -Wall -Wextra -Wpedantic)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ilist PUBLIC -Werror -fsanitize=address -fsanitize=undefined)
    target_link_options(ilist PUBLIC -Werror -fsanitize=address -fsanitize=undefined)
endif()

install(
        TARGETS ilist
        EXPORT ilistTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/ilist
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/ilist
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        EXPORT ilistTargets
        FILE ilistTargets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/ilist/cmake
)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/ilistConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/ilistConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/ilist/cmake"
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/ilistConfigVersion.cmake"
        VERSION 0.1.0
        COMPATIBILITY SameMajorVersion
)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ilistConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ilistConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/ilist/cmake"
)
