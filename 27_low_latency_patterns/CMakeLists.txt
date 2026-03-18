add_executable(27_low_latency_patterns main.cpp)
target_link_libraries(27_low_latency_patterns PRIVATE Threads::Threads)
target_compile_options(27_low_latency_patterns PRIVATE -march=native -O3)
