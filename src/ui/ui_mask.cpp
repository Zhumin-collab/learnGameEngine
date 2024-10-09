//
// created by yzm on 2024/10/7
//

#define RTTR_DLL

#include <vector>
#include <rttr/registration>

#include "ui_mask.h"
#include "component/game_object.h"
#include "renderer/texture2d.h"
#include "renderer/material.h"
#include "renderer/mesh_render.h"
#include "render_device/render_device.h"
#include "utils/debug.h"

RTTR_REGISTRATION{
    rttr::registration::class_<UIMask>("UIMask")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIMask::UIMask()
{

}

UIMask::~UIMask()
{

}

void UIMask::OnEnable()
{

}

void UIMask::Update()
{
    Component::Update();
    if(m_texture==nullptr)
    {
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
        material->Parse("material/ui_mask.mat");
        material->SetTexture("u_diffuse_texture", m_texture);

        auto mesh_render = dynamic_cast<MeshRender*>(game_object()->add_component("MeshRender"));
        mesh_render->SetMaterial(material);
    }
}

void UIMask::OnPreRender()
{
    Component::OnPreRender();
    RenderDevice::instance()->Enable(RenderDevice::STENCIL_TEST);
    glClearStencil(0);__CHECK_GL_ERROR__
    glStencilFunc(GL_NEVER,0x0,0xFF);__CHECK_GL_ERROR__
    glStencilOp(GL_INCR,GL_INCR,GL_INCR);__CHECK_GL_ERROR__

}

void UIMask::OnPostRender()
{
    Component::OnPostRender();
}

void UIMask::OnDisable()
{
    RenderDevice::instance()->Disable(RenderDevice::STENCIL_TEST);
}