// Created by yzm on 2024/9/16

#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
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


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLint mvp_location, vpos_location, vcol_location,a_uv_location;
GLuint kVBO, kEBO;
GLuint kVAO;
MeshFilter* mesh_filter = nullptr;

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

void GeneratorVertexArrayObject()
{
    glGenVertexArrays(1, &kVAO);
}

void GeneratorBufferObject()
{
    glGenBuffers(1, &kVBO);
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh_filter->mesh()->vertex_num*sizeof(MeshFilter::Vertex), mesh_filter->mesh()->vertexs_data, GL_STATIC_DRAW);

    glGenBuffers(1, &kEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->mesh()->vertex_index_num*sizeof(unsigned short), mesh_filter->mesh()->vertex_index_data, GL_STATIC_DRAW);

    glBindVertexArray(kVAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);

        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(MeshFilter::Vertex), 0);
        glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float)*3));
        glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float)*(3+4)));

        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray(vcol_location);
        glEnableVertexAttribArray(a_uv_location);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);

    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


int main()
{
    Application::set_data_path("E:/learnGameEngine/data/");
    
    init_opengl();

    mesh_filter = new MeshFilter();
    mesh_filter->loadMesh("E:/learnGameEngine/data/model/cube.mesh");

    Material* material = new Material();

    material->Parse("material/cube.mat");

    GLuint gl_program_id = material->shader()->gl_program_id();
    mvp_location = glGetUniformLocation(gl_program_id, "u_mvp");
    vpos_location = glGetAttribLocation(gl_program_id, "a_pos");
    vcol_location = glGetAttribLocation(gl_program_id, "a_color");
    a_uv_location = glGetAttribLocation(gl_program_id, "a_uv");

    GeneratorVertexArrayObject();
    GeneratorBufferObject();

    while(!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glm::mat4 model, view, projection, mvp;

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

        model = trans * scale* rotation;

        view = glm::lookAt(
            glm::vec3(0.f, 0.f, 10.f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f)
        );

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;


        glUseProgram(gl_program_id);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE); //开启背面剔除

            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            auto textures = material->textures();
            for(int texture_index = 0; texture_index < textures.size(); texture_index++)
            {

                glActiveTexture(GL_TEXTURE0 + texture_index);
                glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->texture_id());
                glUniform1i(glGetUniformLocation(gl_program_id, textures[texture_index].first.c_str()), texture_index);
            }

            glBindVertexArray(kVAO);
            {
                glDrawElements(GL_TRIANGLES, mesh_filter->mesh()->vertex_index_num, GL_UNSIGNED_SHORT, 0);
            }
            glBindVertexArray(0);

        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}