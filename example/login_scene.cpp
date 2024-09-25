//
// Creared by yzm on 2024/9/23
//
#define RTTR_DLL

#include <rttr/registration>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext.hpp>

#include "login_scene.h"
#include "utils/application.h"
#include "utils/screen.h"
#include "renderer/camera.h"
#include "renderer/material.h"
#include "renderer/mesh_filter.h"
#include "renderer/mesh_render.h"
#include "component/game_object.h"
#include "renderer/texture2d.h"
#include "component/transform.h"
#include "control/key_code.h"
#include "renderer/font.h"

RTTR_REGISTRATION
{
    rttr::registration::class_<LoginScene>("LoginScene")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

void LoginScene::Awake()
{
    GameObject* game_object = new GameObject("main_camera");
    
    m_transform_camera1 = dynamic_cast<Transform*>(game_object->add_component("Transform"));
    m_transform_camera1->set_position(glm::vec3(0,0,10));
    m_camera_1 = dynamic_cast<Camera*>(game_object->add_component("Camera"));
    m_camera_1->set_depth(0);
    m_last_mouse_position = Input::mousePosition();

    CreateFishSoupPot();
    CreateFont();

}

void LoginScene::CreateFishSoupPot()
{
    GameObject* game_object = new GameObject("fish_soup_pot");
    game_object->set_layer(0x01);

    m_transform = dynamic_cast<Transform*>(game_object->add_component("Transform"));

    MeshFilter* mesh_filter = dynamic_cast<MeshFilter*>(game_object->add_component("MeshFilter"));
    mesh_filter->loadMesh("mesh/fish_soup_pot.mesh");

    MeshRender* mesh_render = dynamic_cast<MeshRender*>(game_object->add_component("MeshRender"));
    auto material = new Material();
    material->Parse("material/fish_soup_pot.xml");
    mesh_render->SetMaterial(material);
}

void LoginScene::CreateFont()
{
    std::vector<MeshFilter::Vertex> vertices = {
        {{-1.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
        {{1.f, -1.f, 1.f}, {1.f, 1.f, 1.f, 1.f}, {1.f, 0.f}},
        {{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f, 1.f}, {1.f, 1.f}},
        {{-1.f, -1.f, 1.f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 1.f}}
    };

    std::vector<unsigned short> indexs = {
        0, 1, 2,
        0, 2, 3
    };

    auto go = new GameObject("quad_draw_font");
    go->set_layer(0x01);

    auto transform = dynamic_cast<Transform*>(go->add_component("Transform"));
    transform->set_position(glm::vec3(2, 0, 0));

    auto mesh_filter = dynamic_cast<MeshFilter*>(go->add_component("MeshFilter"));
    mesh_filter->CreateMesh(vertices, indexs);

    m_material = new Material();
    m_material->Parse("material/quad_draw_font.mat");

    auto mesh_render = dynamic_cast<MeshRender*>(go->add_component("MeshRender"));
    mesh_render->SetMaterial(m_material);

    Font* font = Font::LoadFromFile("font/hkyuan.ttf", 500);
    font->LoadCharacter('A');

    m_material->SetTexture("u_diffuse_texture",font->font_texture());
}

void LoginScene::Update()
{

    m_camera_1->SetView(glm::vec3(0,0,0), glm::vec3(0.f, 1.f, 0.f));
    m_camera_1->SetProjection(60.f, Screen::aspect_ratio(), 1.f, 1000.f);

    if(Input::GetKeyDown(KEY_CODE_R))
    {
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        glm::vec3 rotation = m_transform->rotation();
        rotation.y = rotate_eulerAngle;
        m_transform->set_rotation(rotation);
    }

    if(Input::GetKeyDown(KEY_CODE_LEFT_ALT)&& Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        float degrees = Input::mousePosition().x - m_last_mouse_position.x;
        glm::mat4 old_mat4 = glm::mat4(1.f);

        glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.f, 1.f, 0.f));
        glm::vec4 old_pos = glm::vec4(m_transform_camera1->position(), 1.f);
        glm::vec4 new_pos = rotate_mat4 * old_pos;
        m_transform_camera1->set_position(glm::vec3(new_pos));

    }

    m_last_mouse_position = Input::mousePosition();

    m_transform_camera1->set_position(m_transform_camera1->position() * ((10 - Input::mouse_scroll()) / 10.f));

}
