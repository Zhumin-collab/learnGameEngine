cmake_minimum_required(VERSION 3.15)

project(HelloOpenGL VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_DIR "depends/glfw/include")
set(GLAD_DIR "depends/glad/include")
set(GLM_DIR "depends/glm/include")
set(STB_DIR "depends/stb/include")
set(TIMETOOL_DIR "depends/timetool")

include_directories(${GLFW_DIR} ${GLAD_DIR} ${GLM_DIR} ${STB_DIR} ${TIMETOOL_DIR})

add_library(glad STATIC depends/glad/src/glad_gl.c)

link_directories("depends/glfw/libs")

add_executable(HelloOpenGL main.cpp src/texture2d.cpp src/renderer/mesh_filter.cpp)

target_include_directories(HelloOpenGL PRIVATE src)

target_link_libraries(HelloOpenGL PRIVATE glfw3 glad)
