#include <iostream>
#include <assert.h>

#include "input.h"
#include "key_code.h"

std::unordered_map<unsigned char, unsigned char> Input::m_keys_map;
vec2_ushort Input::m_mouse_position = {0, 0};
short Input::m_mouse_scroll = 0;

bool Input::GetKey(unsigned char key_code)
{
    return m_keys_map.count(key_code) > 0;
}

bool Input::GetKeyDown(unsigned char key_code)
{
    if(m_keys_map.count(key_code) == 0)
    {
        return false;
    }
    return m_keys_map[key_code] == KEY_ACTION_DOWN;
}

bool Input::GetKeyUp(unsigned char key_code)
{
    if(m_keys_map.count(key_code) == 0)
    {
        return false;
    }
    return m_keys_map[key_code] == KEY_ACTION_UP;
}

bool Input::GetMouseButton(unsigned short mouse_button_index)
{
    return GetKey(mouse_button_index);
}

bool Input::GetMouseButtonDown(unsigned short mouse_button_index)
{
    return GetKeyDown(mouse_button_index);
}

bool Input::GetMouseButtonUp(unsigned short mouse_button_index)
{
    return GetKeyUp(mouse_button_index);
}

void Input::RecordKey(int key_code, unsigned char key_action)
{
    m_keys_map[key_code] = key_action;
}

void Input::Update()
{
    for(auto it = m_keys_map.begin(); it != m_keys_map.end();)
    {
        if(it->second == KEY_ACTION_UP)
        {
            it = m_keys_map.erase(it);
        }
        else
        {
            it++;
        }
    }

    m_mouse_scroll = 0;
}