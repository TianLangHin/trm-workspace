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

# Advanced C++ (CMake) Lesson 4: Using functions in the CMake script to automate definitions.

function(add_builder width)
  # Advanced C++ (CMake) Lesson 3: Adding custom build targets to the toolchain.
  add_custom_target(set-width-${width}
    COMMAND ${CMAKE_COMMAND} -D TREE_WIDTH=${width} ${CMAKE_BINARY_DIR}
    COMMENT "Setting the game tree width to ${width}."
    VERBATIM
  )
endfunction()

function(add_runner depth)
  # Advanced C++ (CMake) Lesson 3: Adding custom targets to also run the executable.
  add_custom_target(set-depth-${depth}
    COMMAND (echo "${depth}\n") > temp.txt
    COMMAND sss < temp.txt
    COMMAND rm temp.txt
    DEPENDS sss
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Setting the game tree depth to ${depth} and running the SSS* simulator."
    VERBATIM
  )
endfunction()

# Advanced C++ (CMake) Lesson 6: Automating build configurations using for-each loops.
foreach (w 2 3 4 5 6 7 8 9 10)
  add_builder(${w})
endforeach()

foreach (d 2 3 4 5 6 7 8 9 10)
  add_runner(${d})
endforeach()
