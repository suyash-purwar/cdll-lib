include(GNUInstallDirs)

add_library(cdll SHARED cdll.c)

message("${CMAKE_INSTALL_INCLUDEDIR}")

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
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/calc
)

install(
        EXPORT cdllTargets
        FILE cdllTargets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cdll
)
