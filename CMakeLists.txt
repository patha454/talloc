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
    ${PROJECT_SOURCE_DIR}/src/talloc.c
    ${PROJECT_SOURCE_DIR}/src/ref-tree.c
    ${PROJECT_SOURCE_DIR}/src/reference.c
    ${PROJECT_SOURCE_DIR}/src/hash.c
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

add_executable(talloc_demo
    ${PROJECT_SOURCE_DIR}/src/evaluation/test-main.c
)

add_executable(1-alloc-normal
    ${PROJECT_SOURCE_DIR}/src/evaluation/1-alloc-normal.c
)
add_executable(1-alloc-talloc
    ${PROJECT_SOURCE_DIR}/src/evaluation/1-alloc-talloc.c
)

target_include_directories(talloc_demo PRIVATE include)
target_include_directories(1-alloc-talloc PRIVATE include)

target_link_libraries(talloc_demo talloc)
target_link_libraries(1-alloc-talloc talloc)

set(CPACK_PACKAGE_VENDOR "H Paterson")
set(CPACK_PACKAGE_CONTACT "H Paterson <harley.paterson@postgrad.otago.ac.nz>")
set(CPACK_PACKAGE_DESCRIPTION "Experimental tracking allocator.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
