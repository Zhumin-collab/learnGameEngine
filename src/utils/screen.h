#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
    static int width() { return m_width; }
    static int height() { return m_height; }

    static float aspect_ratio() { return m_aspect_ratio; }
    static void set_width(int width){
        m_width = width;
        calculate_aspect_ratio();
    }
    static void set_height(int height){
        m_height = height;
        calculate_aspect_ratio();
    }
    static void set_width_height(int width, int height){
        m_width = width;
        m_height = height;
        calculate_aspect_ratio();
    }
private:
    static void calculate_aspect_ratio(){
        m_aspect_ratio = (float)m_width / (float)m_height;
    }
private:
    static int m_width;
    static int m_height;
    static float m_aspect_ratio;
};


#endif // SCREEN_H