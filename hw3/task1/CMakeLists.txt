cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp 
                MatrixGraph.cpp 
                MatrixGraph.h 
                IGraph.h 
                ListGraph.cpp 
                ListGraph.h
                SetGraph.cpp
                ArcGraph.cpp)
