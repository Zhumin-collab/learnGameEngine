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
set(FREETYPE "depends/freetype/include/freetype2")
set(SPDLOG "depends/spdlog/include")

include_directories(${GLFW_DIR} 
                    ${GLAD_DIR} 
                    ${GLM_DIR} 
                    ${STB_DIR} 
                    ${TIMETOOL_DIR} 
                    ${XML_DIR}
                    ${RTTR}
                    ${FREETYPE}
                    ${SPDLOG}
                    )

add_library(glad STATIC depends/glad/src/glad_gl.c)

link_directories("depends/glfw/libs" "depends/rttr/lib" "depends/freetype/lib" "depends/spdlog/lib")

file(GLOB_RECURSE SOURCES "src/**/*.cpp")

add_executable(LearnGameEngine 
                ${SOURCES} 
                example/main.cpp 
                example/login_scene.cpp
                )

target_include_directories(LearnGameEngine PRIVATE src)

target_link_libraries(LearnGameEngine PRIVATE glfw3 glad rttr_core_d freetyped spdlogd)
