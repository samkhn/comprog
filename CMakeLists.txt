cmake_minimum_required(VERSION 3.5)

project(comprog
	DESCRIPTION "Survey of various data structures and algorithms in C++"
	LANGUAGES CXX)

# Since we only use debug builds
if(MSVC)
	add_compile_options(/std:c++17 /Zi /EHsc)
else()
	add_compile_options(-std=c++17 -g)
endif()

# Binary and Xor
# e.g. use Xor to find [two] missing numbers from a contiguous list
add_executable(bitmanip_demo src/bitmanip_demo.cpp)
add_executable(xor_demo src/xor_demo.cpp)

# Circular Queue with a contiguous array
# TODO: implement with a linked list
add_library(cirq_lib STATIC lib/cirq.cpp include/cirq.hpp)
target_include_directories(cirq_lib PUBLIC ./)
add_executable(cirq_demo src/cirq_demo.cpp)
target_link_libraries(cirq_demo PUBLIC cirq_lib)

# Graphs, the one and only
add_library(graph_lib STATIC lib/graph.cpp include/graph.hpp)
target_include_directories(graph_lib PUBLIC ./)
add_executable(graph_demo src/graph_demo.cpp)
target_link_libraries(graph_demo PUBLIC graph_lib)

# List aka Single/double linked list
# TODO: cirq for another implementation of double linked list
add_library(list_lib STATIC lib/list.cpp include/list.hpp)
target_include_directories(list_lib PUBLIC ./)
add_executable(list_demo src/list_demo.cpp)
target_link_libraries(list_demo PUBLIC list_lib)

# Tries are used for dictionaries and fast string lookups
add_library(trie_lib STATIC lib/trie.cpp include/trie.hpp)
target_include_directories(trie_lib PUBLIC ./)
add_executable(trie_demo src/trie_demo.cpp)
target_link_libraries(trie_demo PUBLIC trie_lib)

# Techniques
# Monotonic Stack to find Next/PrevGreater elements
add_executable(monotonic_stack src/monotonic_stack.cpp)

# Use sliding window to track LongestSubstrWithSomeProperty
add_executable(sliding_window src/sliding_window.cpp)

# Substring search w/ Rabin Karp and Knuth Morris Pratt
add_executable(substr_search src/substr_search.cpp)

# Use two heaps to find median
add_executable(two_heap_median src/two_heap_median.cpp)


