cmake_minimum_required(VERSION 3.15)
project(forth)

set(CMAKE_CXX_STANDARD 14)

add_executable(forth main.cpp Functor.h)