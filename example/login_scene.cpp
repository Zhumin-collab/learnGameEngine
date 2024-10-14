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
#include "ui/ui_image.h"
#include "ui/ui_mask.h"
#include "ui/ui_text.h"
#include "ui/ui_button.h"


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
    CreateUI();

}

void LoginScene::CreateFishSoupPot()
{
    GameObject* game_object = new GameObject("fishsoup_pot");
    game_object->set_layer(0x01);

    m_transform = dynamic_cast<Transform*>(game_object->add_component("Transform"));

    MeshFilter* mesh_filter = dynamic_cast<MeshFilter*>(game_object->add_component("MeshFilter"));
    mesh_filter->loadMesh("model/fishsoup_pot.mesh");

    MeshRender* mesh_render = dynamic_cast<MeshRender*>(game_object->add_component("MeshRender"));
    auto material = new Material();
    material->Parse("material/fishsoup_pot.mat");
    mesh_render->SetMaterial(material);
}

void LoginScene::CreateFont()
{
    std::string str = "Captain";
    Font* font = Font::LoadFromFile("font/hkyuan.ttf", 100);
    auto character_vec = font->LoadStr(str);

    int offset_x = 0;
    for(auto character:character_vec)
    {
        offset_x+=2;
        std::vector<MeshFilter::Vertex> vertices = {
            {{-1.f+offset_x, 2.f, 1.f}, {1.f, 0.f, 0.f, 1.f}, {character->left_top_x, character->right_bottom_y}},
            {{1.f+offset_x,  2.f, 1.f}, {1.f, 0.f, 0.f, 1.f}, {character->right_bottom_x, character->right_bottom_y}},
            {{1.f+offset_x,  4.f, 1.f}, {0.f, 1.f, 0.f, 1.f}, {character->right_bottom_x, character->left_top_y}},
            {{-1.f+offset_x, 4.f, 1.f}, {0.f, 1.f, 0.f, 1.f}, {character->left_top_x, character->left_top_y}}
        };

        std::vector<unsigned short> indexs = {
            0, 1, 2,
            0, 2, 3
        };

        auto go = new GameObject("quad_draw_font");
        go->set_layer(0x01);

        auto transform = dynamic_cast<Transform*>(go->add_component("Transform"));
        transform->set_position(glm::vec3(-8.f, 0.f, 0.f));

        auto mesh_filter = dynamic_cast<MeshFilter*>(go->add_component("MeshFilter"));
        mesh_filter->CreateMesh(vertices, indexs);

        m_material = new Material();
        m_material->Parse("material/quad_draw_font.mat");

        auto mesh_render = dynamic_cast<MeshRender*>(go->add_component("MeshRender"));
        mesh_render->SetMaterial(m_material);



        m_material->SetTexture("u_diffuse_texture",font->font_texture());
    }
}

void LoginScene::CreateUI()
{
    auto go_camera_ui = new GameObject("ui_camera");
    auto transform_camera_ui = dynamic_cast<Transform*>(go_camera_ui->add_component("Transform"));
    transform_camera_ui->set_position(glm::vec3(0.f, 0.f, 10.f));

    auto camera_ui = dynamic_cast<Camera*>(go_camera_ui->add_component("Camera"));
    camera_ui->set_depth(1);
    camera_ui->set_chulling_mask(0x02);
    
    camera_ui->set_clear_flag(GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    camera_ui->SetView(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    camera_ui->SetOrthographic(-Screen::width()/2.,Screen::width()/2.,-Screen::height()/2.,Screen::height()/2.,-100.f,100.f);

    auto go_ui = new GameObject("image_mod_bag");
    go_ui->set_layer(0x02);
    go_ui->add_component("Transform");

    auto ui_image = dynamic_cast<UIImage*>(go_ui->add_component("UIImage"));
    ui_image->set_texture(Texture2D::LoadFromFile("images/mod_bag.cpt"));

    auto go_mask= new GameObject("mask_mod_bag");
    go_mask->set_layer(0x02);
    go_mask->set_parent(go_ui);

    auto transform_ui_mask = dynamic_cast<Transform*>(go_mask->add_component("Transform"));
    auto ui_mask_mod_bag = dynamic_cast<UIMask*>(go_mask->add_component("UIMask"));
    ui_mask_mod_bag->set_texture(Texture2D::LoadFromFile("images/mod_bag_mask.cpt"));

    Font* font = Font::LoadFromFile("font/hkyuan.ttf", 24);
    auto go_text = new GameObject("text");
    go_text->set_layer(0x02);
    
    auto transform_text = dynamic_cast<Transform*>(go_text->add_component("Transform"));

    transform_text->set_position({0.f,-200.f,0.f});

    auto ui_text = dynamic_cast<UIText*>(go_text->add_component("UIText"));
    ui_text->set_font(font);
    ui_text->set_text("a");
    ui_text->set_color(glm::vec4(1.f, 0.f, 0.f, 1.f));

    auto go_button_image_normal = new GameObject("btn_power");
    go_button_image_normal->set_layer(0x02);
    go_button_image_normal->add_component("Transform");
    auto ui_image_button_image_normal = dynamic_cast<UIImage*>(go_button_image_normal->add_component("UIImage"));
    ui_image_button_image_normal->set_texture(Texture2D::LoadFromFile("images/btn_power.cpt"));

    auto go_button_image_press = new GameObject("btn_power_press");
    go_button_image_press->set_layer(0x02);
    go_button_image_press->add_component("Transform");
    auto ui_image_button_image_press = dynamic_cast<UIImage*>(go_button_image_press->add_component("UIImage"));
    ui_image_button_image_press->set_texture(Texture2D::LoadFromFile("images/btn_power_press.cpt"));

    auto go_button = new GameObject("button");
    go_button->set_layer(0x02);
    auto transform_ui_button = dynamic_cast<Transform*>(go_button->add_component("Transform"));
    transform_ui_button->set_position({100.f, -200.f, 0.f});
    auto ui_button = dynamic_cast<UIButton*>(go_button->add_component("UIButton"));
    ui_button->set_image_normal(ui_image_button_image_normal);
    ui_button->set_image_press(ui_image_button_image_press);
    ui_button->set_click_callback([=](){
        go_mask->set_active(!go_mask->active());
    });
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
