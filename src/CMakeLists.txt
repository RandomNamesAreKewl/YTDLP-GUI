cmake_minimum_required(VERSION 3.20)

project(YTDLPGui)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(UILy)

add_executable(yt-dlp-gui main.cpp)
target_include_directories(yt-dlp-gui PUBLIC UILy)
target_link_libraries(yt-dlp-gui PRIVATE UILy gui glfw OpenGL::GL)
