#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <iostream>
#include <vector>

#include "../component/component.h"
#include "../renderer/mesh_filter.h"

class Texture2D;
class UIImage : public Component
{
public:
    UIImage();
    ~UIImage() override;

    Texture2D* texture() { return m_texture; }

    void set_texture(Texture2D* texture) { m_texture = texture; }

public:
    void Awake() override;
    void Update() override;
private:
    Texture2D* m_texture = nullptr;

};


#endif