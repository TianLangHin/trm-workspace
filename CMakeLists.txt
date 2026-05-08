cmake_minimum_required(VERSION 3.20)
project(SSS VERSION 1.0 DESCRIPTION "Implementing SSS*")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Advanced C++ (CMake) Lesson 3: defining the output directory for the binary executable.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/../bin")

# Advanced C++ (CMake) Lesson 2: defining the executable name from the main C++ program.
add_executable(sss main.cpp)

target_compile_definitions(sss PRIVATE TREE_WIDTH=${TREE_WIDTH})

# Advanced C++ (CMake) Lesson 3: Integrating libraries.
target_link_directories(sss
  PRIVATE
    sss_algos
    sss_tree
)

target_include_directories(sss
  PRIVATE
    algos
    tree
)

