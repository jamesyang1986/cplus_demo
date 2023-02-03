cmake_minimum_required(VERSION 3.22)
project(cplus_demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(cplus_demo main.cpp model/Student.cpp model/Student.h ds/LinkedList.cpp ds/LinkedList.h ds/Dict.cpp ds/Dict.h)
