cmake_minimum_required(VERSION 3.5)

project(comprog
  DESCRIPTION "Survey of various data structures and algorithms in C++"
  LANGUAGES CXX)

# Since we only use debug builds, settings global compiler flags
# In `modern cmake` don't do this
if (MSVC)
  add_compile_options(/std:c++17 /Zi /EHsc)
else ()
  add_compile_options(-std=c++17 -g)
endif ()

add_executable (bits src/structures/bits.cpp)
add_executable (bited src/techniques/bited.cpp)  # bit editing
add_executable (xor src/structures/xor.cpp)

add_executable (array src/structures/array.cpp)
add_executable (circular_queue src/structures/circular_queue.cpp)
add_executable (forward_list src/structures/forward_list.cpp)
add_executable (intervals src/structures/intervals.cpp)
add_executable (sliding_window src/techniques/sliding_window.cpp)  # to find the longest substring that meets some invariant
add_executable (substr_search src/techniques/substr_search.cpp)  # w/ rabin karp and knuth morris pratt
add_executable (monotonic_stack src/techniques/monotonic_stack.cpp)  # monotonic Stack to find next or previous greater elements
add_executable (two_heap_median src/techniques/two_heap_median.cpp)
add_executable (kway-mergesort src/techniques/kway-mergesort.cpp)  # using priority queues

add_executable (bst src/structures/bst.cpp)
add_executable (heap src/structures/heap.cpp)
add_executable (trie src/structures/trie.cpp)
add_executable (graph src/structures/graph.cpp)
add_executable (schedule src/techniques/schedule.cpp)  # uses topological sort

add_executable (fib src/techniques/dp/fib.cpp)
add_executable (01knapsack src/techniques/dp/01knapsack.cpp)
add_executable (partition-equal-subset src/techniques/dp/partition-equal-subset.cpp)  # partition-equal-subset is a variant of 0/1 knapsack
add_executable (staircase src/techniques/dp/staircase.cpp)
add_executable (lps src/techniques/dp/lps.cpp)
add_executable (lcs src/techniques/dp/lcs.cpp)
add_executable (transpose src/techniques/transpose.cpp)  # in-place transpose w/ follow the cycles technique

