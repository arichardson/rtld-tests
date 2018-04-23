cmake_minimum_required(VERSION 3.8)
project(rtld_tests)

set(CMAKE_CXX_STANDARD 11)

if(NOT "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Invalid C compiler ${CMAKE_C_COMPILER_ID}, must be CHERI clang")
endif()
if(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Invalid C compiler ${CMAKE_CXX_COMPILER_ID}, must be CHERI clang")
endif()


add_subdirectory(constructor_order)
