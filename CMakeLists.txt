cmake_minimum_required(VERSION 3.26)
project(exam_task C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(tests)
add_executable(exam_task main.c
        tests/test_exam_task.c
        tests/test_exam_task.h)
