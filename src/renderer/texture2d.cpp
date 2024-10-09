//
// Created by yzm on 2024/9/17
// 图片加载与解析
//

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <stopwatch.h>
#include <fstream>
#include <glm/glm.hpp>
#include <stb_truetype.h>

#include "texture2d.h"
#include "../utils/application.h"
#include "../utils/debug.h"

Texture2D::Texture2D():m_gl_texture_format(0),m_width(0),m_height(0),m_mipmap_level(0),m_texture_id(0)
{
    
}
Texture2D::~Texture2D()
{
    if(m_texture_id>0)
        glDeleteTextures(1, &m_texture_id);__CHECK_GL_ERROR__
}

void Texture2D::UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type, unsigned char* data)
{
    if(width<=0||height<=0)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture_id);__CHECK_GL_ERROR__
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);__CHECK_GL_ERROR__
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, client_format, data_type, data);__CHECK_GL_ERROR__
}
Texture2D* Texture2D::LoadFromFile(std::string image_file_path)
{
    if(image_file_path.empty())
    {
        DEBUG_LOG_ERROR("image file path is empty");
        return nullptr;
    }
    Texture2D* texture2d = new Texture2D();

    timetool::StopWatch stopwatch;
    stopwatch.start();
        std::ifstream in(Application::data_path()+image_file_path, std::ios::binary);
        TpcFileHead tcp;
        in.read((char*)&tcp, sizeof(TpcFileHead));
        unsigned char* data = (unsigned char*)malloc(tcp.compress_size);
        in.read((char*)data, tcp.compress_size);
        in.close();
    stopwatch.stop();
    std::cout << "load image cost:" << stopwatch.milliseconds() << "ms" << std::endl;

    texture2d->m_gl_texture_format = tcp.gl_texture_format;
    texture2d->m_width = tcp.width;
    texture2d->m_height = tcp.height;
    texture2d->m_mipmap_level = tcp.mipmap_level;


    glGenTextures(1, &(texture2d->m_texture_id));__CHECK_GL_ERROR__
    glBindTexture(GL_TEXTURE_2D, texture2d->m_texture_id);__CHECK_GL_ERROR__

    stopwatch.restart();
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, tcp.gl_texture_format, tcp.width, tcp.height, 0, tcp.compress_size, data);__CHECK_GL_ERROR__

    stopwatch.stop();
    std::cout << "upload image cost:" << stopwatch.milliseconds() << "ms" << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);__CHECK_GL_ERROR__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);__CHECK_GL_ERROR__

    free(data);


    return texture2d;
}

Texture2D* Texture2D::Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format, unsigned int data_type, unsigned char* data)
{
    Texture2D* texture2d = new Texture2D();
    texture2d->m_gl_texture_format = server_format;
    texture2d->m_width = width;
    texture2d->m_height = height;
    texture2d->m_mipmap_level = 0;

    glGenTextures(1, &(texture2d->m_texture_id));__CHECK_GL_ERROR__
    glBindTexture(GL_TEXTURE_2D, texture2d->m_texture_id);__CHECK_GL_ERROR__
    glTexImage2D(GL_TEXTURE_2D, 0, server_format, width, height, 0, client_format, data_type, data);__CHECK_GL_ERROR__

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);__CHECK_GL_ERROR__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);__CHECK_GL_ERROR__
    
    return texture2d;
}