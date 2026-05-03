cmake_minimum_required(VERSION 4.1)
project(untitled5 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled5 main.c
        waveform.c
        io.c
        waveform.h
        io.h)
