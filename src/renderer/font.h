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

    struct Character{
        float left_top_x;
        float left_top_y;
        float right_bottom_x;
        float right_bottom_y;
        Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y):
            left_top_x(left_top_x),left_top_y(left_top_y),right_bottom_x(right_bottom_x),right_bottom_y(right_bottom_y){}
    };

    std::vector<Character*> LoadStr(std::string str);

private:
    unsigned short m_font_size = 20;
    char* m_font_file_buffer = nullptr;
    FT_Library m_ft_library;
    FT_Face m_ft_face;
    Texture2D* m_font_texture;
    unsigned short m_font_texture_width = 1024;
    unsigned short m_font_texture_fill_x= 0;
    unsigned short m_font_texture_fill_y= 0;

    std::unordered_map<char, Character*> m_character_map;

public:
    static Font* LoadFromFile(std::string font_file_path, unsigned short font_size);

    static Font* GetFont(std::string font_file_path);

private:
    static std::unordered_map<std::string, Font*> m_font_map;
};


#endif