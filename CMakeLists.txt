cmake_minimum_required(VERSION 3.26)
project(UnixLab4 C)

set(CMAKE_C_STANDARD 23)

add_executable(UnixLab4 intercept-keyboard.c
        memory-read.c
)
