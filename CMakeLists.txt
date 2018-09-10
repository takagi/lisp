cmake_minimum_required (VERSION 3.1)
project (lisp)

# Includes
include(cmake/third-party.cmake)

# Configure options
option(DISABLE_TEST "Disable building test" OFF)

# C++ setup
set(CMAKE_CXX_STANDARD 14)
include_directories("${PROJECT_SOURCE_DIR}")

# Test
if(NOT DISABLE_TEST)
    get_third_party(gtest)
    enable_testing()
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
    include_directories(${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
endif()

add_subdirectory(lisp)
