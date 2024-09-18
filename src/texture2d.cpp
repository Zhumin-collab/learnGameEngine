//
// Created by yzm on 2024/9/17
// 图片加载与解析
//

#include "texture2d.h"
#include <stb_image.h>

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
{
    Texture2D* texture2d = new Texture2D();
    stbi_set_flip_vertically_on_load(true);
    int channels_in_file;
    unsigned char* data = stbi_load(image_file_path.c_str(), &texture2d->width, &texture2d->height, &channels_in_file, 0);

    if (data != nullptr)
    {
        switch (channels_in_file)
        {
            case 1:
                texture2d->gl_texture_format = GL_ALPHA;
                break;
            case 3:
                texture2d->gl_texture_format = GL_RGB;
                break;
            case 4:
                texture2d->gl_texture_format = GL_RGBA;
                break;

        }
    }
    glGenTextures(1, &texture2d->texture_id);
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2d->width, texture2d->height, 0, texture2d->gl_texture_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    stbi_image_free(data);

    return texture2d;
}