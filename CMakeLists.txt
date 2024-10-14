cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        UC.cpp
        UC.h
        Lesson.cpp
        Lesson.h
        ReadFiles.cpp
        ReadFiles.h
        Student.cpp
        Student.h
        Class.cpp
        Class.h
        Interface.cpp
        Interface.h
        Request.cpp
        Request.h
)
