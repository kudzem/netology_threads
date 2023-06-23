cmake_minimum_required(VERSION 3.10])
project(cpp_new_features_review)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
add_executable(pg "demo.cpp" "safe_queue.h" "thread_pool.h")