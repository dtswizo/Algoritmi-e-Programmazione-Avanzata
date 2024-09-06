cmake_minimum_required(VERSION 3.20)
project(EX_03 C)

set(CMAKE_C_STANDARD 99)

add_executable(EX_03 main.c pg.h inv.h pg.c inv.c)
