cmake_minimum_required(VERSION 3.20)

project(UILy)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(imgui)

include_directories(${OPENGL_INCLUDE_DIR} .)

add_library(UILy SHARED UILy/window.cpp UILy/rendering.cpp UILy/debug.cpp)
