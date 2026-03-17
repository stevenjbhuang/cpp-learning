add_executable(28_robotics_patterns main.cpp)
target_link_libraries(28_robotics_patterns PRIVATE Threads::Threads)
target_compile_options(28_robotics_patterns PRIVATE -O2)
