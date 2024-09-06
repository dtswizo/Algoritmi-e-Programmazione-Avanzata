cmake_minimum_required(VERSION 3.20)
project(EX_01 C)

set(CMAKE_C_STANDARD 99)

add_executable(EX_01 main.c data.h data.c ora.h ora.c titolo.h titolo.c ListTitoli.h listTitoli.c quotazioneGiornaliera.h quotazioneGiornaliera.c BST.h BST.c)
