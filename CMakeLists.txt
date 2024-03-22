cmake_minimum_required(VERSION 3.26)
project(Project5 C)

set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -pedantic -Wno-unused-function)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(Project5 main.c
        Boolean.c
        Circuit.c
        Gates.c
        strdup.c)
