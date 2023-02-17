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

# Data structures

# Binary and Xor
# e.g. use Xor to find [two] missing numbers from a contiguous list
add_executable(bitmanip_demo bitmanip_demo.cpp)
add_executable(xor_demo xor_demo.cpp)

# Circular Queue with a contiguous array
# TODO: implement with a linked list too for comparison?
add_executable(cirq_demo cirq_demo.cpp)

# Graphs, the one and only
add_executable(graph_demo graph_demo.cpp)

# List aka Single/double linked list
# TODO: cirq for another implementation of double linked list
add_executable(list_demo list_demo.cpp)

# Tries are used for dictionaries and fast string lookups
add_executable(trie_demo trie_demo.cpp)

# Techniques

# Monotonic Stack to find Next/PrevGreater elements
add_executable(monotonic_stack monotonic_stack.cpp)

# Use sliding window to track LongestSubstrWithSomeProperty
add_executable(sliding_window sliding_window.cpp)

# Substring search w/ Rabin Karp and Knuth Morris Pratt
add_executable(substr_search substr_search.cpp)

# Use two heaps to find median
add_executable(two_heap_median two_heap_median.cpp)


