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
add_executable(bits src/structures/bits.cpp)
add_executable(xor src/structures/xor.cpp)

# Sequential data src/structures
add_executable(array src/structures/array.cpp)
add_executable(circular_queue src/structures/circular_queue.cpp)
add_executable(forward_list src/structures/forward_list.cpp)
add_executable(intervals src/structures/intervals.cpp)

# Tree data src/structures
add_executable(bst src/structures/bst.cpp)
add_executable(heap src/structures/heap.cpp)
add_executable(trie src/structures/trie.cpp)

# Graph data src/structures
add_executable(graph src/structures/graph.cpp)

# DP
add_executable(dp src/techniques/dp.cpp)

# Job scheduling w/ topological sort
add_executable(schedule src/techniques/schedule.cpp)

# Monotonic Stack to find next or previous greater elements
# I don't really like it but it seems interesting
add_executable(monotonic_stack src/techniques/monotonic_stack.cpp)

# Use sliding window to find the longest substring that meets some invariant
add_executable(sliding_window src/techniques/sliding_window.cpp)

# Substring search w/ Rabin Karp and Knuth Morris Pratt
add_executable(substr_search src/techniques/substr_search.cpp)

# Use two heaps to find median. Pretty interesting.
add_executable(two_heap_median src/techniques/two_heap_median.cpp)

# Merging sorted lists with PQs
add_executable(kway-mergesort src/techniques/kway-mergesort.cpp)

# In-place transpose of matrices using "follow-the-cycles"
add_executable(transpose src/techniques/transpose.cpp)
