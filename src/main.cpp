// Created by yzm on 2024/9/16

#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "utils/application.h"
#include "renderer/mesh_filter.h"
#include "renderer/texture2d.h"
#include "renderer/shader.h"
#include "renderer/material.h"

#include "renderer/mesh_render.h"


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;

void init_opengl()
{
    std::cout<<"init_opengl"<<std::endl;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(1);
}



int main()
{
    Application::set_data_path("E:/learnGameEngine/data/");
    
    init_opengl();

    MeshFilter* mesh_filter = new MeshFilter();
    mesh_filter->loadMesh("E:/learnGameEngine/data/model/cube.mesh");

    Material* material = new Material();
    material->Parse("material/cube.mat");

    MeshRender* mesh_render = new MeshRender();

    mesh_render->SetMaterial(material);
    mesh_render->SetMeshFilter(mesh_filter);


    while(!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glClearColor(49.f/255.f, 77.f/255.f, 121.f/255.f, 1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0.f, 0.f, 0.f));

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1.f;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle));       
        
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

        glm::mat4 model = trans * scale* rotation;

        glm::mat4 view = glm::lookAt(
            glm::vec3(0.f, 0.f, 10.f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f)
        );

        glm::mat4 projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        glm::mat4 mvp = projection * view * model;

        mesh_render->SetMVP(mvp);
        mesh_render->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}