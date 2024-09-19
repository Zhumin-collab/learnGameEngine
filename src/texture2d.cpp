//
// Created by yzm on 2024/9/17
// 图片加载与解析
//

#include "texture2d.h"
#include <stb_image.h>
#include <stopwatch.h>
#include <fstream>

// Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
// {
//     Texture2D* texture2d = new Texture2D();
//     stbi_set_flip_vertically_on_load(true);
//     int channels_in_file;
//     timetool::StopWatch stopwatch;
//     stopwatch.start();
//     unsigned char* data = stbi_load(image_file_path.c_str(), &texture2d->width, &texture2d->height, &channels_in_file, 0);
//     stopwatch.stop();
//     std::cout << "load image cost:" << stopwatch.milliseconds() << "ms" << std::endl;
//     if (data != nullptr)
//     {
//         switch (channels_in_file)
//         {
//             case 1:
//                 texture2d->gl_texture_format = GL_ALPHA;
//                 break;
//             case 3:
//                 texture2d->gl_texture_format = GL_RGB;
//                 break;
//             case 4:
//                 texture2d->gl_texture_format = GL_RGBA;
//                 break;

//         }
//     }
//     glGenTextures(1, &texture2d->texture_id);
//     glBindTexture(GL_TEXTURE_2D, texture2d->texture_id);

//     stopwatch.restart();
//     glTexImage2D(GL_TEXTURE_2D, texture2d->mipmap_level, GL_COMPRESSED_RGB, texture2d->width, texture2d->height, 0, texture2d->gl_texture_format, GL_UNSIGNED_BYTE, data);
//     stopwatch.stop();
//     std::cout << "upload image cost:" << stopwatch.milliseconds() << "ms" << std::endl;

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

//     stbi_image_free(data);

//     return texture2d;
// }

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
{
    Texture2D* texture2d = new Texture2D();

    timetool::StopWatch stopwatch;
    stopwatch.start();
        std::ifstream in(image_file_path, std::ios::binary);
        TpcFileHead tcp;
        in.read((char*)&tcp, sizeof(TpcFileHead));
        unsigned char* data = (unsigned char*)malloc(tcp.compress_size);
        in.read((char*)data, tcp.compress_size);
        in.close();
    stopwatch.stop();
    std::cout << "load image cost:" << stopwatch.milliseconds() << "ms" << std::endl;

    texture2d->gl_texture_format = tcp.gl_texture_format;
    texture2d->width = tcp.width;
    texture2d->height = tcp.height;
    texture2d->mipmap_level = tcp.mipmap_level;


    glGenTextures(1, &texture2d->texture_id);
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_id);

    stopwatch.restart();
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, tcp.gl_texture_format, tcp.width, tcp.height, 0, tcp.compress_size, data);
    stopwatch.stop();
    std::cout << "upload image cost:" << stopwatch.milliseconds() << "ms" << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(data);


    return texture2d;
}

void Texture2D::CompressImageFile(std::string& image_file_path, std::string& output_file_path)
{
    Texture2D* texture2d = LoadFromFile(image_file_path);

    //1. 获取是否压缩成功
    GLint compress_success = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compress_success);

    //2. 获取压缩后的大小
    GLint compress_size = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);

    //3. 获取压缩后的格式
    GLint compress_format = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compress_format);
    
    //4. 从GPU中，将显存中保存的压缩好的纹理数据，下载到内存
    void* img = malloc(compress_size);
    glGetCompressedTexImage(GL_TEXTURE_2D, 0, img);

    //5. 将内存中的数据保存到文件
    std::ofstream out(output_file_path, std::ios::binary);

    TpcFileHead head;
    head.type[0] = 'c';
    head.type[1] = 'p';
    head.type[2] = 't';
    head.mipmap_level = 0;
    head.width = texture2d->width;
    head.height = texture2d->height;
    head.gl_texture_format = compress_format;
    head.compress_size = compress_size;

    out.write((char*)&head, sizeof(TpcFileHead));

    out.write((char*)img, compress_size);
    
    out.close();
}