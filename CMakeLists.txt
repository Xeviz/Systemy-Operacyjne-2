cmake_minimum_required(VERSION 3.27)
project(sysprojekt)

add_executable(sysprojekt main.cpp
        Application.cpp
        Application.h
        Ball.cpp
        Ball.h
        Square.cpp
        Square.h)


set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)


target_link_libraries(sysprojekt glfw OpenGL::GL)
link_directories(/usr/lib/x86_64-linux-gnu)