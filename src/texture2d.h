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
    Texture2D(){};
    ~Texture2D(){};

public:
    static Texture2D* LoadFromFile(std::string& image_file_path);

public:
    GLenum gl_texture_format;

    int width;
    int height;

    GLuint texture_id; // 纹理ID

};







#endif // TEXTURE2D_H