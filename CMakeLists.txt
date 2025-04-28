cmake_minimum_required(VERSION 3.10)
project(DCDLHelper)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include header files
include_directories(include)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

# Create the executable
add_executable(dcdl-helper ${SOURCES})

# (Optional) Extra warning flags
target_compile_options(dcdl-helper PRIVATE -Wall -Wextra -pedantic)
