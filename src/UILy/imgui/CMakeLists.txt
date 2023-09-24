cmake_minimum_required(VERSION 3.20)

project(ImGui)

file(GLOB_RECURSE SOURCES "**.cpp")

add_library(gui ${SOURCES})
