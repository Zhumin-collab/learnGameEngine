//
// Created by yzm on 2024/9/24
//

#include <fstream>
#include <string.h>

#include "font.h"
#include "freetype/ftbitmap.h"
#include "../utils/application.h"
#include "../utils/debug.h"
#include "texture2d.h"

std::unordered_map<std::string, Font*> Font::m_font_map;

Font* Font::LoadFromFile(std::string font_file_path, unsigned short font_size)
{
    Font* font = GetFont(font_file_path);
    if(font!=nullptr)
    {
        return font;
    }
    std::ifstream input_file_stream(Application::data_path() + font_file_path, std::ios::binary);
    input_file_stream.seekg(0, std::ios::end);
    int len = input_file_stream.tellg();
    input_file_stream.seekg(0, std::ios::beg);
    char* font_file_buffer = new char[len];
    input_file_stream.read(font_file_buffer, len);

    FT_Library ft_library = nullptr;
    FT_Face ft_face = nullptr;
    FT_Init_FreeType(&ft_library);//初始化FreeType库
    FT_Error error = FT_New_Memory_Face(ft_library, (FT_Byte*)font_file_buffer, len, 0, &ft_face);
    if(error!=0)
    {
        DEBUG_LOG_ERROR("load font file failed: {}", font_file_path);
        return nullptr;
    }

    FT_Select_Charmap(ft_face, FT_ENCODING_UNICODE);

    FT_F26Dot6 ft_size = (FT_F26Dot6)(font_size * (1 << 6));
    FT_Set_Char_Size(ft_face, ft_size, 0, 72, 72);

    if(ft_face==nullptr)
    {
        DEBUG_LOG_ERROR("FT_Ser_Char_Size error!");
        return nullptr;
    }

    font = new Font();
    font->m_font_size = font_size;
    font->m_font_file_buffer = font_file_buffer;
    font->m_ft_library = ft_library;
    font->m_ft_face = ft_face;
    m_font_map[font_file_path] = font;

    unsigned char* pixels = (unsigned char*)malloc(font->m_font_texture_width * font->m_font_texture_width);
    memset(pixels, 0, font->m_font_texture_width * font->m_font_texture_width);
    font->m_font_texture = Texture2D::Create(font->m_font_texture_width, font->m_font_texture_width, GL_RED, GL_RED, GL_UNSIGNED_BYTE, pixels);
    free(pixels);

    return font;
}

void Font::LoadCharacter(char ch)
{
    if(m_character_map.find(ch)!=m_character_map.end())
    {
        return;
    }
    FT_Load_Glyph(m_ft_face, FT_Get_Char_Index(m_ft_face, ch), FT_LOAD_DEFAULT);

    FT_Glyph ft_glyph;
    FT_Get_Glyph(m_ft_face->glyph, &ft_glyph);

    FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);

    FT_BitmapGlyph ft_bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
    FT_Bitmap& ft_bitmap = ft_bitmap_glyph->bitmap;

    if(m_font_texture_fill_x + ft_bitmap.width >= m_font_texture_width)
    {
        m_font_texture_fill_x = 0;
        m_font_texture_fill_y += m_font_size;
    }

    if(m_font_texture_fill_y + m_font_size >= m_font_texture_width)
    {
        spdlog::error("font texture is full!");
        return;
    }

    m_font_texture->UpdateSubImage(m_font_texture_fill_x,m_font_texture_fill_y,ft_bitmap.width,ft_bitmap.rows,GL_RED,GL_UNSIGNED_BYTE,ft_bitmap.buffer);

    Character* character = new Character(
        (float)m_font_texture_fill_x / m_font_texture_width,
        (float)m_font_texture_fill_y / m_font_texture_width,
        (float)(m_font_texture_fill_x + ft_bitmap.width) / m_font_texture_width,
        (float)(m_font_texture_fill_y + ft_bitmap.rows) / m_font_texture_width
    );
    m_character_map[ch] = character;

    m_font_texture_fill_x += ft_bitmap.width;
}

Font* Font::GetFont(std::string font_file_path)
{
    auto iter = m_font_map.find(font_file_path);
    if(iter!=m_font_map.end())
    {
        return iter->second;
    }
    return nullptr;
}

std::vector<Font::Character*> Font::LoadStr(std::string str)
{
    std::vector<Character*> characters;
    for(auto ch:str)
    {
        LoadCharacter(ch);
    }

    for(auto ch:str)
    {
        auto character = m_character_map[ch];
        if(character!=nullptr)
        {
            characters.push_back(character);
        }
        else
        {
            spdlog::error("character not found: {}", ch);
            continue;
        }
    }

    return characters;
}