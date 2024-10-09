//
// Created by yzm on 2024/10/7
//

#ifndef UI_MASK_H
#define UI_MASK_H

#include "component/component.h"
#include "renderer/mesh_filter.h"

class Texture2D;
class UIMask : public Component
{
public:
    UIMask();
    ~UIMask() override;

    Texture2D* texture() { return m_texture; }

    void set_texture(Texture2D* texture) { m_texture = texture; }

public:
    void OnEnable() override;

    void Update() override;

    void OnPreRender() override;

    void OnPostRender() override;

    void OnDisable() override;
private:
    Texture2D* m_texture = nullptr;

};


#endif // UI_MASK_H