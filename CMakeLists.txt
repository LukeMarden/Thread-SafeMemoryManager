cmake_minimum_required(VERSION 3.15)
project(Thread_SafeMemoryManager C)

set(CMAKE_C_STANDARD 99)

add_executable(Thread_SafeMemoryManager main.c part1.c part1.h part2.c part2.h part3.c part3.h part1_test.c part2_test.c part3_test.c)