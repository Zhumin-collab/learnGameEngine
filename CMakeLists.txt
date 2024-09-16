cmake_minimum_required(VERSION 3.15)

project(HelloOpenGL VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_DIR "depends/glfw/include")
set(GLAD_DIR "depends/glad/include")


include_directories(${GLFW_DIR} ${GLAD_DIR})

add_library(glad STATIC depends/glad/src/glad_gl.c)

link_directories("depends/glfw/libs")


add_executable(HelloOpenGL main.cpp)

target_link_libraries(HelloOpenGL PRIVATE glfw3 glad)
