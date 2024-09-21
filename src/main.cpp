// Created by yzm on 2024/9/16

#define GLFW_INCLUDE_NONE
#define RTTR_DLL
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
#include "renderer/camera.h"
#include "component/transform.h"
#include "component/game_object.h"
#include "component/component.h"



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

    GameObject* game_object = new GameObject("game_object");
    
    auto transform=dynamic_cast<Transform*>(game_object->add_component("Transform"));

    auto mesh_filter = dynamic_cast<MeshFilter*>(game_object->add_component<MeshFilter>());
    mesh_filter->loadMesh("model/fishsoup_pot.mesh");

    auto mesh_render = dynamic_cast<MeshRender*>(game_object->add_component<MeshRender>());

    Material* material = new Material();
    material->Parse("material/fishsoup_pot.mat");
    mesh_render->SetMaterial(material);

    auto go_camera = new GameObject("main_camera");
    auto transform_camera = dynamic_cast<Transform*>(go_camera->add_component("Transform"));
    transform_camera->set_position(glm::vec3(0.f, 0.f, 10.f));
    auto camera = dynamic_cast<Camera*>(go_camera->add_component("Camera"));

    while(!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        camera->SetView(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
        camera->SetProjection(60.f, ratio, 1.f, 1000.f);
        camera->clear();
        
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        glm::vec3 rotation = transform->rotation();
        rotation.y = rotate_eulerAngle;
        transform->set_rotation(rotation);

        mesh_render->SetView(camera->view_mat4());
        mesh_render->SetProjection(camera->projection_mat4());
        mesh_render->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}