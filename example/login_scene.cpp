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
#include "utils/time.h"
#include "audio/studio/audio_studio.h"


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

     //CreateFishSoupPot();

    // CreateQuad();

    CreateAudioSource();
    CreateAudioListener();

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

void LoginScene::CreateQuad()
{
    std::vector<MeshFilter::Vertex> vertex_vector = {
        {{-1.f,-1.f,1.f}, {1.f,1.f,1.f,1.f}, {0.f,0.f}},
        {{1.f,-1.f,1.f}, {1.f,1.f,1.f,1.f}, {1.f,0.f}},
        {{1.f,1.f,1.f}, {1.f,1.f,1.f,1.f}, {1.f,1.f}},
        {{-1.f,1.f,1.f}, {1.f,1.f,1.f,1.f}, {0.f,1.f}}
    };

    std::vector<unsigned short> vertex_index_vector = {
        0,1,2,
        0,2,3
    };

    auto go = new GameObject("quad_draw_font");
    go->set_layer(0x01);

    auto transform = dynamic_cast<Transform*>(go->add_component("Transform"));
    transform->set_position(glm::vec3(2.f,0.f,5.f));

    auto mesh_filter = dynamic_cast<MeshFilter*>(go->add_component("MeshFilter"));
    mesh_filter->CreateMesh(vertex_vector, vertex_index_vector);

    m_material = new Material();
    m_material->Parse("material/fmod_play_2d_sound_tips.mat");

    auto mesh_render = dynamic_cast<MeshRender*>(go->add_component("MeshRender"));
    mesh_render->SetMaterial(m_material);
}

void LoginScene::CreateAudioSource()
{
    GameObject* go = new GameObject("audio_source_bgm");

    auto transform = dynamic_cast<Transform*>(go->add_component("Transform"));
    auto mesh_filter = dynamic_cast<MeshFilter*>(go->add_component("MeshFilter"));
    mesh_filter->loadMesh("model/sphere.mesh");

    auto mesh_renderer = dynamic_cast<MeshRender*>(go->add_component("MeshRender"));
    auto material = new Material();
    material->Parse("material/sphere_audio_source_3d_music.mat");
    mesh_renderer->SetMaterial(material);

    AudioStudio::loadBankFile("audio/test.bank");
    AudioStudio::loadBankFile("audio/test.strings.bank");

    m_audio_studio_event = AudioStudio::CreateEventInstance("event:/footstep");
}

void LoginScene::CreateAudioListener()
{
    auto go = new GameObject("Player");
    m_transform_player = dynamic_cast<Transform*>(go->add_component("Transform"));
    m_transform_player->set_position(glm::vec3(2.f, 0.f, 0.f));

    auto mesh_filter = dynamic_cast<MeshFilter*>(go->add_component("MeshFilter"));
    mesh_filter->loadMesh("model/sphere.mesh");

    auto mesh_render = dynamic_cast<MeshRender*>(go->add_component("MeshRender"));
    auto material = new Material();
    material->Parse("material/sphere_audio_source_3d_listener.mat");
    mesh_render->SetMaterial(material);

    AudioStudio::setListenerAttributes(0.f, 0.f, 0.f);
}


void LoginScene::Update()
{

    m_camera_1->SetView(glm::vec3(0,0,0), glm::vec3(0.f, 1.f, 0.f));
    m_camera_1->SetProjection(60.f, Screen::aspect_ratio(), 1.f, 1000.f);


    if(Input::GetKeyDown(KEY_CODE_LEFT_ALT)&& Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        float degrees = Input::mousePosition().x - m_last_mouse_position.x;
        glm::mat4 old_mat4 = glm::mat4(1.f);

        glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.f, 1.f, 0.f));
        glm::vec4 old_pos = glm::vec4(m_transform_camera1->position(), 1.f);
        glm::vec4 new_pos = rotate_mat4 * old_pos;
        m_transform_camera1->set_position(glm::vec3(new_pos));

    }

    if(Input::GetKeyUp(KEY_CODE_S)){
        m_audio_studio_event->Start();
    }

    if(Input::GetKeyUp(KEY_CODE_1)){
        m_audio_studio_event->SetParameterByName("groundtype",0.0f);
    }else if(Input::GetKeyUp(KEY_CODE_2)){
        m_audio_studio_event->SetParameterByName("groundtype",1.0f);
    }else if(Input::GetKeyUp(KEY_CODE_3)){
        m_audio_studio_event->SetParameterByName("groundtype",2.0f);
    }



    m_last_mouse_position = Input::mousePosition();

    m_transform_camera1->set_position(m_transform_camera1->position() * ((10 - Input::mouse_scroll()) / 10.f));


    glm::mat4 rotate_mat4 = glm::rotate(glm::mat4(1.f), glm::radians(Time::deltaTime()*60), glm::vec3(0.f, 0.f, 1.f));
    glm::vec4 old_pos = glm::vec4(m_transform_player->position(), 1.f);
    glm::vec4 new_pos = rotate_mat4 * old_pos;
    m_transform_player->set_position(glm::vec3(new_pos));
}

