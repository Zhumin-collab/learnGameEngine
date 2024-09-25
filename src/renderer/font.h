#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <unordered_map>
#include <freetype/ftglyph.h>

class Texture2D;
class Font
{
public:
    void LoadCharacter(char ch);

    Texture2D* font_texture(){return m_font_texture;}

private:
    unsigned short m_font_size = 20;
    char* m_font_file_buffer = nullptr;
    FT_Library m_ft_library;
    FT_Face m_ft_face;
    Texture2D* m_font_texture;
    unsigned short m_font_texture_width = 1024;

public:
    static Font* LoadFromFile(std::string font_file_path, unsigned short font_size);

    static Font* GetFont(std::string font_file_path);

private:
    static std::unordered_map<std::string, Font*> m_font_map;
};


#endif