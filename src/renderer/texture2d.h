//
// created by yzm on 2024/9/17
// 图片加载与解析
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/gl.h>




class Texture2D
{
private:
    Texture2D();

public:
    ~Texture2D();

    void UpdateSubImage(int x,int y,int width,int height,unsigned int client_format,unsigned int data_type,unsigned char* data);

public:
    struct TpcFileHead
    {
        char type[3];
        int mipmap_level;
        int width;
        int height;
        int gl_texture_format;
        int compress_size;
    };

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

public:
    static Texture2D* LoadFromFile(std::string image_file_path);

    static Texture2D* Create(unsigned short width,unsigned short height,unsigned int server_format,unsigned int client_format,unsigned int data_type,unsigned char* data);

};







#endif // TEXTURE2D_H