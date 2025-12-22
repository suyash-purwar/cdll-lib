find_package(PkgConfig REQUIRED)

add_executable(test_cdll tests.c)

pkg_check_modules(CRITERION REQUIRED IMPORTED_TARGET criterion)

target_link_libraries(test_cdll PRIVATE PkgConfig::CRITERION)

add_test(NAME cdll_tests COMMAND test_cdll)
