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
set(FMOD "depends")
set(FMOD2 "depends/fmod/api/core/inc")
add_compile_definitions(USE_FMOD_STUDIO)
include_directories(${GLFW_DIR} 
                    ${GLAD_DIR} 
                    ${GLM_DIR} 
                    ${STB_DIR} 
                    ${TIMETOOL_DIR} 
                    ${XML_DIR}
                    ${RTTR}
                    ${FREETYPE}
                    ${SPDLOG}
                    ${FMOD}
                    ${FMOD2}
                    )

add_library(glad STATIC depends/glad/src/glad_gl.c)

link_directories("depends/glfw/libs" 
                 "depends/rttr/lib" 
                 "depends/freetype/lib" 
                 "depends/spdlog/lib" 
                 "depends/fmod/api/core/lib/x64/"
                 "depends/fmod/api/studio/lib/x64/"
                 )

file(GLOB_RECURSE SOURCES "src/**/*.cpp")

add_executable(LearnGameEngine 
                ${SOURCES} 
                example/main.cpp 
                example/login_scene.cpp
                )

target_include_directories(LearnGameEngine PRIVATE src)

target_link_libraries(LearnGameEngine PRIVATE glfw3 glad rttr_core_d freetyped spdlogd fmod_vc fmodL_vc fmodstudio_vc fmodstudioL_vc)
