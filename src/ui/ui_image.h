#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <iostream>
#include <vector>

#include "../component/component.h"
#include "../renderer/mesh_filter.h"
#include "renderer/texture2d.h"
class Texture2D;
class UIImage : public Component
{
public:
    UIImage();
    ~UIImage() override;

    Texture2D* texture() { return m_texture; }

    void set_texture(Texture2D* texture) { 
        m_texture = texture; 
        m_width = m_texture->width();
        m_height = m_texture->height();
    }

    int width() { return m_width; }
    int height() { return m_height; }
public:
    void Update() override;

    void OnPreRender() override;

    void OnPostRender() override;
private:
    Texture2D* m_texture = nullptr;
    int m_width;
    int m_height;

};


#endif