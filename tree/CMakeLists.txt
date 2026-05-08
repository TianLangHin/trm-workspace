# Advanced C++ (CMake) Lesson 3: Declaring libraries within subfolders
# and attaching them as targets to the main one.
add_library(sss_tree STATIC
  computation.hpp
  tree_node.hpp
)

target_include_directories(sss_tree
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
