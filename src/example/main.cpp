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
#include "control/input.h"
#include "control/key_code.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout<<"mouse_button_callback:"<<button<<","<<action<<std::endl;
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::set_mousePosition(xpos, ypos);
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::set_mouse_scroll(yoffset);
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

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);

}



int main()
{
    Application::set_data_path("E:/learnGameEngine/data/");
    
    init_opengl();

    GameObject* game_object = new GameObject("game_object");
    game_object->set_layer(0x01);
    
    auto transform=dynamic_cast<Transform*>(game_object->add_component("Transform"));

    auto mesh_filter = dynamic_cast<MeshFilter*>(game_object->add_component<MeshFilter>());
    mesh_filter->loadMesh("model/fishsoup_pot.mesh");

    auto mesh_render = dynamic_cast<MeshRender*>(game_object->add_component<MeshRender>());

    Material* material = new Material();
    material->Parse("material/fishsoup_pot.mat");
    mesh_render->SetMaterial(material);

    auto go_camera_1 = new GameObject("main_camera");
    auto transform_camera = dynamic_cast<Transform*>(go_camera_1->add_component("Transform"));
    transform_camera->set_position(glm::vec3(0.f, 0.f, 10.f));
    auto camera_1 = dynamic_cast<Camera*>(go_camera_1->add_component("Camera"));

    auto go_camera_2 = new GameObject("second_camera");
    auto transform_camera_2 = dynamic_cast<Transform*>(go_camera_2->add_component("Transform"));
    transform_camera_2->set_position(glm::vec3(1.f, 0.f, 10.f));
    auto camera_2 = dynamic_cast<Camera*>(go_camera_2->add_component("Camera"));
    camera_2->set_clear_flag(GL_DEPTH_BUFFER_BIT);

    camera_1->set_depth(0);
    camera_2->set_depth(1);

    camera_1->set_chulling_mask(0x01);
    camera_2->set_chulling_mask(0x02);

    vec2_ushort last_frame_mouse_position = Input::mousePosition();


    while(!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        camera_1->SetView(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
        camera_1->SetProjection(60.f, ratio, 1.f, 1000.f);
        
        camera_2->SetView(glm::vec3(transform_camera_2->position().x,0,0), glm::vec3(0.f, 1.f, 0.f));
        camera_2->SetProjection(60.f, ratio, 1.f, 1000.f);

        if(Input::GetKeyDown(KEY_CODE_R))
        {
            static float rotate_eulerAngle = 0.f;
            rotate_eulerAngle += 0.1f;
            glm::vec3 rotation = transform->rotation();
            rotation.y = rotate_eulerAngle;
            transform->set_rotation(rotation);
        }

        if(Input::GetKeyDown(KEY_CODE_LEFT_ALT)&& Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            float degrees = Input::mousePosition().x - last_frame_mouse_position.x;
            glm::mat4 old_mat4 = glm::mat4(1.f);

            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.f, 1.f, 0.f));
            glm::vec4 old_pos = glm::vec4(transform_camera->position(), 1.f);
            glm::vec4 new_pos = rotate_mat4 * old_pos;
            transform_camera->set_position(glm::vec3(new_pos));

        }

        last_frame_mouse_position = Input::mousePosition();

        transform_camera->set_position(transform_camera->position() * ((10 - Input::mouse_scroll()) * 0.1f));


        Input::Update();
        
        Camera::Foreach([&](){
            mesh_render->Render();
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}