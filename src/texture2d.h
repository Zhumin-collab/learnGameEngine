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
    Texture2D():mipmap_level(0)
    {
        
    };
    ~Texture2D(){};

public:
    static Texture2D* LoadFromFile(std::string& image_file_path);

    static void CompressImageFile(std::string& image_file_path, std::string& output_file_path);

public:
    GLenum gl_texture_format;

    int width;
    int height;
    int mipmap_level;
    
    GLuint texture_id; // 纹理ID

};







#endif // TEXTURE2D_H