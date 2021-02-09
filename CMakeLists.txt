cmake_minimum_required(VERSION 3.16)

cmake_policy(VERSION 3.16)

project(
  dpatch
  VERSION 0.0.0
  DESCRIPTION "Experimental tracking allocator."
  LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
include(CPack)

add_library(talloc SHARED
    ${PROJECT_SOURCE_DIR}/src/binary-tree.c
    ${PROJECT_SOURCE_DIR}/src/status.c
)

target_include_directories(talloc PRIVATE include)

set(TARGET talloc PROPERTY C_STANDARD 99)

target_compile_options(
    talloc PRIVATE
    "SHELL:-W"
    "SHELL:-Wall"
    "SHELL:-Wextra"
    "SHELL:-Werror"
    "SHELL:-pedantic"
)

add_executable(talloc_unit_tests_status
    ${PROJECT_SOURCE_DIR}/tests/status.c
)

add_executable(talloc_unit_tests_binary_tree
  ${PROJECT_SOURCE_DIR}/tests/binary-tree.c
)

find_package(cmocka REQUIRED)

target_include_directories(talloc_unit_tests_status PRIVATE
    include
    ${CMOCKA_INCLUDE_DIR}
)

target_include_directories(talloc_unit_tests_binary_tree PRIVATE
    include
    ${CMOCKA_INCLUDE_DIR}
)

target_link_libraries(talloc_unit_tests_status
    talloc
    ${CMOCKA_LIBRARY}
)

target_link_libraries(talloc_unit_tests_binary_tree
    talloc
    ${CMOCKA_LIBRARY}
)

add_test(NAME talloc_unit_tests_stats COMMAND talloc_unit_tests_status)
add_test(NAME talloc_unit_tests_binary_tree COMMAND talloc_unit_tests_binary_tree)

set(CPACK_PACKAGE_VENDOR "H Paterson")
set(CPACK_PACKAGE_CONTACT "H Paterson <harley.paterson@postgrad.otago.ac.nz>")
set(CPACK_PACKAGE_DESCRIPTION "Experimental tracking allocator.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
