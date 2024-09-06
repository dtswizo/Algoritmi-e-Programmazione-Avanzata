cmake_minimum_required(VERSION 3.20)
project(EX_03 C)

set(CMAKE_C_STANDARD 99)

add_executable(EX_03 pg.h inv.h pgList.h equipArray.h invArray.h gdr.c pgList.c pg.c inv.c invArray.c equipArray.c)
