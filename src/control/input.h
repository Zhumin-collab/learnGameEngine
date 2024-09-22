#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <glm/glm.hpp>

struct vec2_ushort
{
    unsigned short x;
    unsigned short y;
};

class Input
{
public:

    static bool GetKey(unsigned char key_code);

    static bool GetKeyDown(unsigned char key_code);

    static bool GetKeyUp(unsigned char key_code);

    static void RecordKey(int key_code, unsigned char key_action);

    static void Update();

    static bool GetMouseButton(unsigned short mouse_button_index);

    static bool GetMouseButtonDown(unsigned short mouse_button_index);

    static bool GetMouseButtonUp(unsigned short mouse_button_index);

    static vec2_ushort mousePosition(){return m_mouse_position;};

    static void set_mousePosition(unsigned short x, unsigned short y) {m_mouse_position.x = x; m_mouse_position.y = y;};

    static short mouse_scroll(){return m_mouse_scroll;};

    static void set_mouse_scroll(short scroll) {m_mouse_scroll += scroll;};

private:
    static std::unordered_map<unsigned char, unsigned char> m_keys_map;
    static vec2_ushort m_mouse_position;
    static short m_mouse_scroll;
};



#endif // INPUT_H