#include <fstream>
#include <iostream>
#include <glad/gl.h>

#include "shader.h"
#include "../utils/application.h"

std::unordered_map<std::string, Shader*> Shader::m_shader_map;

Shader::Shader()
{

}

Shader::~Shader()
{

}

Shader* Shader::Find(std::string shader_name)
{
    auto it = m_shader_map.find(shader_name);
    if (it != m_shader_map.end())
    {
        return it->second;
    }

    Shader* shader = new Shader();
    shader->Parse(shader_name);
    m_shader_map[shader_name] = shader;

    return shader;
}

void Shader::Parse(std::string shader_name)
{
    std::string vertex_shader_path = Application::data_path() + shader_name + ".vs";
    std::string fragment_shader_path = Application::data_path() +  shader_name + ".fs";

    std::ifstream vertex_shader_file(vertex_shader_path);
    std::string vertex_shader_text((std::istreambuf_iterator<char>(vertex_shader_file)), std::istreambuf_iterator<char>());

    std::ifstream fragment_shader_file(fragment_shader_path);
    std::string fragment_shader_text((std::istreambuf_iterator<char>(fragment_shader_file)), std::istreambuf_iterator<char>());

    CreateGPUProgram(vertex_shader_text.c_str(), fragment_shader_text.c_str());
}

void Shader::CreateGPUProgram(const char* vertex_shader_text, const char* fragment_shader_text)
{
    //创建顶点Shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);
    //获取编译结果
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
        std::cout << "compile vs error:" << message << std::endl;
    }

    //创建片段Shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);
    //获取编译结果
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
        std::cout << "compile fs error:" << message << std::endl;
    }

    //创建GPU程序
    m_gl_program_id = glCreateProgram();
    //附加Shader
    glAttachShader(m_gl_program_id, vertex_shader);
    glAttachShader(m_gl_program_id, fragment_shader);
    //Link
    glLinkProgram(m_gl_program_id);
    //获取编译结果
    GLint link_status = GL_FALSE;
    glGetProgramiv(m_gl_program_id, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(m_gl_program_id, sizeof(message), 0, message);
        std::cout << "link error:" << message << std::endl;
    }
}

void Shader::Active()
{
    glUseProgram(m_gl_program_id);
}

void Shader::InActive()
{
    glUseProgram(0);
}
