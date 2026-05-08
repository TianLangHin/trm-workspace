# Advanced C++ (CMake) Lesson 3: Declaring libraries within subfolders
# and attaching them as targets to the main one.
add_library(sss_algos STATIC
  alpha_beta.hpp
  sss.hpp
)

target_include_directories(sss_algos
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Advanced C++ (CMake) Lesson 3: Declaring that this sub-library
# depends on another one that is not directly nested.
target_link_libraries(
  PUBLIC sss_tree
)
