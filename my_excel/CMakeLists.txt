cmake_minimum_required(VERSION 3.30)
project(my_excel)

set(CMAKE_CXX_STANDARD 23)

add_executable(my_excel main.cpp
        my_excel.util.h
        my_excel.util.cpp
    )
