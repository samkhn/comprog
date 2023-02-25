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

# Integer data structures
add_executable(bits structures/bits.cpp)
add_executable(xor structures/xor.cpp)

# Sequential data structures
add_executable(array structures/array.cpp)
add_executable(circular_queue structures/circular_queue.cpp)
add_executable(forward_list structures/forward_list.cpp)
add_executable(intervals structures/intervals.cpp)

# Tree data structures
add_executable(bst structures/bst.cpp)
add_executable(heap structures/heap.cpp)
add_executable(trie structures/trie.cpp)

# Graph data structures
add_executable(graph structures/graph.cpp)

# Job scheduling w/ topological sort
add_executable(schedule techniques/schedule.cpp)

# Monotonic Stack to find next or previous greater elements
# I don't really like it but it seems interesting
add_executable(monotonic_stack techniques/monotonic_stack.cpp)

# Use sliding window to find the longest substring that meets some invariant
add_executable(sliding_window techniques/sliding_window.cpp)

# Substring search w/ Rabin Karp and Knuth Morris Pratt
add_executable(substr_search techniques/substr_search.cpp)

# Use two heaps to find median. Pretty interesting.
add_executable(two_heap_median techniques/two_heap_median.cpp)

# Merging sorted lists with PQs
add_executable(kway-mergesort techniques/kway-mergesort.cpp)

# In-place transpose of matrices using "follow-the-cycles"
add_executable(transpose techniques/transpose.cpp)
