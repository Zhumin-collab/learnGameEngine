//
// created by yzm on 2024/10/8
//

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "component/component.h"

class Font;
class MeshRender;
class UIText : public Component
{
public:
    UIText();
    ~UIText();

    void set_font(Font* font) {m_font = font;}
    Font* font() {return m_font;}

    void set_text(std::string text);
    std::string text() {return m_text;}

    void set_color(glm::vec4 color){m_color = color;}
    glm::vec4 color(){return m_color;}

public:
    void Update() override;
    void OnPreRender() override;
    void OnPostRender() override;

private:
    Font* m_font;
    std::string m_text;
    bool m_dirty;
    glm::vec4 m_color;
};



#endif // UI_TEXT_H