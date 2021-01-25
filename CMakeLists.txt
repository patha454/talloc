cmake_minimum_required(VERSION 3.16)

cmake_policy(VERSION 3.16)

project(
  dpatch
  VERSION 0.0.0
  DESCRIPTION "Experimental tracking allocator."
  LANGUAGES C
)

add_library(talloc SHARED
    ${PROJECT_SOURCE_DIR}/talloc.c
)

set(TARGET talloc PROPERTY C_STANDARD 99)

target_compile_options(
    talloc PRIVATE
    "SHELL:-W"
    "SHELL:-Wall"
    "SHELL:-Wextra"
    "SHELL:-Werror"
    "SHELL:-pedantic"
)

set(CPACK_PACKAGE_VENDOR "H Paterson")
set(CPACK_PACKAGE_CONTACT "H Paterson <harley.paterson@postgrad.otago.ac.nz>")
set(CPACK_PACKAGE_DESCRIPTION "Experimental tracking allocator.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
include(CPack)