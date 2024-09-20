//
// created by yzm on 2024/9/17
// 图片加载与解析
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/gl.h>


struct TpcFileHead
{
    char type[3];
    int mipmap_level;
    int width;
    int height;
    int gl_texture_format;
    int compress_size;
};

class Texture2D
{
private:
    Texture2D():m_gl_texture_format(GL_RGBA),m_width(0),m_height(0),m_mipmap_level(0),m_texture_id(0)
    {
        
    };
    ~Texture2D(){};

public:
    static Texture2D* LoadFromFile(std::string& image_file_path);

    static void CompressImageFile(std::string& image_file_path, std::string& output_file_path);

    int mip_map_level() { return m_mipmap_level; }
    int width() { return m_width; }
    int height() { return m_height; }
    GLuint texture_id() { return m_texture_id; }
    GLenum gl_texture_format() { return m_gl_texture_format; }
    
private:
    GLenum m_gl_texture_format;

    int m_width;
    int m_height;
    int m_mipmap_level;
    
    GLuint m_texture_id; // 纹理ID

};







#endif // TEXTURE2D_H