//
// created by yzm on 2024/10/8
//

#define RTTR_DLL

#include <vector>
#include <rttr/registration>

#include "ui_text.h"
#include "component/game_object.h"
#include "renderer/texture2d.h"
#include "renderer/material.h"
#include "renderer/mesh_render.h"
#include "renderer/mesh_filter.h"
#include "renderer/font.h"
#include "render_device/render_device.h"
#include "utils/debug.h"

RTTR_REGISTRATION{
    rttr::registration::class_<UIText>("UIText")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIText::UIText():m_color({1,1,1,1}){

}

void UIText::set_text(std::string text)
{
    if(m_text == text)
    {
        return;
    }

    m_text = text;
    m_dirty = true;
}

void UIText::Update(){
    Component::Update();
    
    if(m_font==nullptr||m_font->font_texture()==nullptr)
    {
        return;
    }

    MeshFilter* mesh_filter = dynamic_cast<MeshFilter*>(game_object()->get_component("MeshFilter"));
    if(mesh_filter==nullptr){
        mesh_filter = dynamic_cast<MeshFilter*>(game_object()->add_component("MeshFilter"));

        auto material = new Material();
        material->Parse("material/ui_text.mat");

        auto mesh_renderer = dynamic_cast<MeshRender*>(game_object()->add_component("MeshRender"));
        mesh_renderer->SetMaterial(material);

        material->SetTexture("u_diffuse_texture", m_font->font_texture());
    }

    if(m_dirty){
        m_dirty = false;

        std::vector<Font::Character*> characters = m_font->LoadStr(m_text);

        std::vector<MeshFilter::Vertex> vertex_vector;

        std::vector<unsigned short>  index_vector(characters.size()*6);

        int x=0;
        std::vector<unsigned short> index = {0,1,2,0,2,3};

        for(int i=0;i<characters.size();i++){

            auto character = characters[i];

            unsigned short width = (character->right_bottom_x-character->left_top_x)*m_font->font_texture()->width();
            unsigned short height = (character->right_bottom_y-character->left_top_y)*m_font->font_texture()->height();

            vertex_vector.insert(vertex_vector.end(),
                {
                {{x,0.f,0.f},m_color,{character->left_top_x,character->right_bottom_y}},
                {{x+width,0.f,0.f},m_color,{character->right_bottom_x,character->right_bottom_y}},
                {{x+width,height,0.f},m_color,{character->right_bottom_x,character->left_top_y}},
                {{x,height,0.f},m_color,{character->left_top_x,character->left_top_y}}
                }
            );

            x+=width;

            for(int j=0;j<index.size();j++){
                index_vector[i*index.size()+j] = index[j]+i*4;
            }
        }
        mesh_filter->CreateMesh(vertex_vector, index_vector);
    }
}

void UIText::OnPreRender(){
    Component::OnPreRender();
}

void UIText::OnPostRender(){
    Component::OnPostRender();
}

UIText::~UIText()
{
    
}