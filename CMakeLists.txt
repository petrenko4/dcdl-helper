cmake_minimum_required(VERSION 3.10.0)
project(dcdl-helper VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCES
    src/*.cpp
)

message(STATUS "Source files: ${SOURCES}")

add_executable(dcdl-helper ${SOURCES})

# find_package(fmt CONFIG REQUIRED)

find_path(EXPRTK_INCLUDE_DIR exprtk.hpp
    PATHS "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include"
)

if(NOT EXPRTK_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find exprtk.hpp")
endif()

target_include_directories(dcdl-helper PRIVATE ${EXPRTK_INCLUDE_DIR})
# target_link_libraries(dcdl-helper PRIVATE fmt::fmt)
target_compile_options(dcdl-helper PRIVATE -Wall -Wextra -pedantic)
enable_testing()

add_executable(unit_tests tests/test_main.cpp)

target_include_directories(unit_tests PRIVATE ${EXPRTK_INCLUDE_DIR} include)

add_test(NAME MyTest COMMAND unit_tests)
