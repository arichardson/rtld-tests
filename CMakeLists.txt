cmake_minimum_required(VERSION 3.8)
project(rtld_tests)

set(CMAKE_CXX_STANDARD 11)

if(NOT "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Invalid C compiler ${CMAKE_C_COMPILER_ID}, must be CHERI clang")
endif()
if(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Invalid C compiler ${CMAKE_CXX_COMPILER_ID}, must be CHERI clang")
endif()

include(GNUInstallDirs)
set(CMAKE_SKIP_RPATH FALSE)
set(CMAKE_SKIP_INSTALL_RPATH FALSE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# TODO: do I really need the full path?
set(CMAKE_INSTALL_RPATH "\$ORIGIN/../${CMAKE_INSTALL_LIBDIR};${CMAKE_INSTALL_FULL_LIBDIR};")

add_subdirectory(constructor_order)
