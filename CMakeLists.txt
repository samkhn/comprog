cmake_minimum_required(VERSION 3.5)

project(comprog
	DESCRIPTION "Survey of various data structures and algorithms in C++"
	LANGUAGES CXX)

# Since we only use debug builds, settings global compiler flags
# In `modern cmake` don't do this
if(MSVC)
	add_compile_options(/std:c++17 /Zi /EHsc)
else()
	add_compile_options(-std=c++17 -g)
endif()

# Data structures

# Bits touches on bitshifting and manipulation (common in some cg circles)
# Also provides a snippet of being able to toggle a bit regardless of initial
# state.
add_executable(bits bits.cpp)

# Xor to find one or two missing numbers from a contiguous list
add_executable(xor xor.cpp)

# cirq, a circular queue, is a core data structure inside the linux kernel.
# Good for producer, consumer pattern (e.g. kernel driver produces, userspace
# consumers).
# TODO: implement with a linked list too for comparison?
# TODO: as mentioned in https://docs.kernel.org/core-api/circular-buffers.html
# the kernel implements it with powers of two, since % is expensive.
# TODO: memory barrier to avoid single lock or atomic primitives
add_executable(circular_queue circular_queue.cpp)

# Graphs. Need I say more? Touches on DFS/BFS, Dijkstra's, Topological Sort.
# TODO: Primm's MST? Seems to use the same `relaxing edge` property that
# Dijkstra's exploits.
add_executable(graph graph.cpp)

# List aka single/double linked list
# TODO: Circular double linked lists are used quite a bit in the linux kernel,
# implement it for fun at some point
add_executable(forward_list forward_list.cpp)

# Tries aka prefix trees are used for dictionaries and fast string lookups
add_executable(trie trie.cpp)

# Techniques

# Monotonic Stack to find next or previous greater elements
# I don't really like it but it seems interesting
add_executable(monotonic_stack monotonic_stack.cpp)

# Use sliding window to find the longest substring that meets some invariant
add_executable(sliding_window sliding_window.cpp)

# Substring search w/ Rabin Karp and Knuth Morris Pratt
# TODO: Upon further inspection, I don't think I implemented the rolling hash
# properly so I'll need to check.
# TODO: benchmark on very long strings (where we can observe the benefits
# of more complex algorithms/prunings).
add_executable(substr_search substr_search.cpp)

# Use two heaps to find median
# This one was nice, interesting, dope, <insert other positive adjectives>
add_executable(two_heap_median two_heap_median.cpp)

# Merge intervals
add_executable(merge_intervals merge_intervals.cpp)
