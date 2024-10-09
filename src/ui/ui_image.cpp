//
// created by yzm on 2024/9/28
//

#define RTTR_DLL
#include <rttr/registration>

#include "ui_image.h"
#include "../utils/debug.h"
#include "../renderer/mesh_filter.h"
#include "../renderer/mesh_render.h"
#include "../renderer/texture2d.h"
#include "../component/game_object.h"
#include "../renderer/material.h"
#include "../render_device/render_device.h"

RTTR_REGISTRATION
{
    rttr::registration::class_<UIImage>("UIImage")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIImage::UIImage()
{
}

UIImage::~UIImage()
{
}


void UIImage::Update()
{
    Component::Update();
    if(m_texture==nullptr)
    {
        SPDLOG_INFO("ui texture is null");
        return;
    }

    MeshFilter* mesh_filter = dynamic_cast<MeshFilter*>(game_object()->get_component("MeshFilter"));
    if(mesh_filter==nullptr)
    {
        std::vector<MeshFilter::Vertex> vertex_vector = {
            {{0.f,0.f,0.f},{1.f,1.f,1.f,1.f},{0.f,0.f}},
            {{m_texture->width(),0.f,0.f},{1.f,1.f,1.f,1.f},{1.f,0.f}},
            {{m_texture->width(),m_texture->height(),0.f},{1.f,1.f,1.f,1.f},{1.f,1.f}},
            {{0.f,m_texture->height(),0.f},{1.f,1.f,1.f,1.f},{0.f,1.f}}
        };

        std::vector<unsigned short> index_vector = {
            0,1,2,
            0,2,3
        };

        mesh_filter = dynamic_cast<MeshFilter*>(game_object()->add_component("MeshFilter"));
        mesh_filter->CreateMesh(vertex_vector, index_vector);

        auto material = new Material();
        material->Parse("material/ui_image.mat");
        material->SetTexture("u_diffuse_texture", m_texture);

        auto mesh_render = dynamic_cast<MeshRender*>(game_object()->add_component("MeshRender"));
        mesh_render->SetMaterial(material);    
    }
}

void UIImage::OnPreRender()
{
    Component::OnPreRender();
    glStencilFunc(GL_EQUAL, 0x1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

}

void UIImage::OnPostRender()
{
    Component::OnPostRender();
    RenderDevice::instance()->Disable(RenderDevice::STENCIL_TEST);
}