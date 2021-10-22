cmake_minimum_required(VERSION 3.20)
project(ITOPR_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ITOPR_3 main.cpp order_task.cpp order_task.h file_manager.cpp file_manager.h order_permutation.cpp order_permutation.h bounds.cpp bounds.h branching.cpp branching.h)
