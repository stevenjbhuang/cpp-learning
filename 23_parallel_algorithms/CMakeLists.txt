add_executable(23_parallel_algorithms main.cpp)
target_link_libraries(23_parallel_algorithms PRIVATE Threads::Threads)

# TBB is required for std::execution::par with Clang on Linux.
# Install: sudo apt install libtbb-dev  (or brew install tbb on macOS)
if(TBB_FOUND)
    target_link_libraries(23_parallel_algorithms PRIVATE TBB::tbb)
    target_compile_definitions(23_parallel_algorithms PRIVATE HAS_TBB=1)
else()
    message(WARNING "TBB not found — 23_parallel_algorithms will build without parallel execution policies.")
    target_compile_definitions(23_parallel_algorithms PRIVATE HAS_TBB=0)
endif()
