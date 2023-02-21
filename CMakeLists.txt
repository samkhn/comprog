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

# Array shifts, rotates, resize (like vector), prefix sum and histograms
add_executable(array array.cpp)

# cirq, a circular queue, is a core data structure inside the linux kernel.
# Good for producer, consumer pattern (e.g. kernel driver produces, userspace
# consumers).
add_executable(circular_queue circular_queue.cpp)

# Pre/post/inorder traversal and de/serializing a binary tree
add_executable(bst bst.cpp)

# Heaps aka PQs
add_executable(heap heap.cpp)

# Graphs. Need I say more? Touches on DFS/BFS, Dijkstra's, Topological Sort.
add_executable(graph graph.cpp)

# List aka single/double linked list
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
add_executable(substr_search substr_search.cpp)

# Use two heaps to find median
# This one was nice, interesting, dope, <insert other positive adjectives>
add_executable(two_heap_median two_heap_median.cpp)

# Comparing, sortin and merging intervals
add_executable(intervals intervals.cpp)

# In-place transpose of matrices
add_executable(transpose transpose.cpp)
