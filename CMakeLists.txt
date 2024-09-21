cmake_minimum_required(VERSION 3.15)

project(LearnGameEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_DIR "depends/glfw/include")
set(GLAD_DIR "depends/glad/include")
set(GLM_DIR "depends/glm/include")
set(STB_DIR "depends/stb/include")
set(TIMETOOL_DIR "depends/timetool")
set(XML_DIR "depends/rapidxml/include")
set(RTTR "depends/rttr/include")

include_directories(${GLFW_DIR} 
                    ${GLAD_DIR} 
                    ${GLM_DIR} 
                    ${STB_DIR} 
                    ${TIMETOOL_DIR} 
                    ${XML_DIR}
                    ${RTTR})

add_library(glad STATIC depends/glad/src/glad_gl.c)

link_directories("depends/glfw/libs" "depends/rttr/lib")

add_executable(LearnGameEngine 
                src/main.cpp 
                src/renderer/texture2d.cpp 
                src/renderer/mesh_filter.cpp
                src/renderer/material.cpp 
                src/renderer/shader.cpp 
                src/utils/application.cpp
                src/renderer/mesh_render.cpp
                src/component/transform.cpp
                src/component/game_object.cpp
                src/component/component.cpp
                src/renderer/camera.cpp
                )

target_include_directories(LearnGameEngine PRIVATE src)

target_link_libraries(LearnGameEngine PRIVATE glfw3 glad rttr_core_d)
