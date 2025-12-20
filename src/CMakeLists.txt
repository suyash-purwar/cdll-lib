include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(cdll SHARED cdll.c)

target_include_directories(
        cdll PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(cdll PRIVATE -Wall -Wextra -Wpedantic)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(cdll PRIVATE -Werror -fsanitize=address -fsanitize=undefined)
endif()

install(
        TARGETS cdll
        EXPORT cdllTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/cdll
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/cdll
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cdll
)

install(
        EXPORT cdllTargets
        FILE CdllTargets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cdll/cmake
)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/CdllConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/CdllConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cdll/cmake"
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/CdllConfigVersion.cmake"
        VERSION 0.1.0
        COMPATIBILITY SameMajorVersion
)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CdllConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CdllConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cdll/cmake"
)
