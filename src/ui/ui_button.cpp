//
// created by yzm on 2024/10/9
//

#define RTTR_DLL
#include <rttr/registration>
#include <glm/ext.hpp>

#include "ui_button.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "utils/debug.h"
#include "utils/screen.h"
#include "control/input.h"
#include "control/key_code.h"
#include "ui_image.h"

RTTR_REGISTRATION{
    rttr::registration::class_<UIButton>("UIButton")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIButton::UIButton():m_press(false),m_image_normal(nullptr){

}

UIButton::~UIButton(){

}

void UIButton::Update(){
    Component::Update();

    if(m_image_normal==nullptr||m_image_press==nullptr){
        return;
    }

    Transform* transform = dynamic_cast<Transform*>(game_object()->get_component("Transform"));

    Transform* transform_image_normal = dynamic_cast<Transform*>(m_image_normal->game_object()->get_component("Transform"));

    Transform* transform_image_press = dynamic_cast<Transform*>(m_image_press->game_object()->get_component("Transform"));

    transform_image_normal->set_position(transform->position());
    transform_image_press->set_position(transform->position());

    if(Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)){
        auto transform_position = transform->position();

        auto mouse_position = Input::mousePosition();

        mouse_position.x = mouse_position.x - Screen::width()/2;
        mouse_position.y = Screen::height()/2 - mouse_position.y;

        float image_normal_width = m_image_normal->width();
        float image_normal_height = m_image_normal->height();

        if((mouse_position.x > transform_position.x&&mouse_position.x < transform_position.x + image_normal_width)&&
            (mouse_position.y > transform_position.y&&mouse_position.y < transform_position.y + image_normal_height)){
            if(m_press){
                return;
            }
            m_press = true;
            if(m_click_callback){
                m_click_callback();
            }
        }else{
            m_press = false;
        }
    }else{
        m_press = false;
    }

    transform_image_normal->game_object()->set_active(!m_press);
    transform_image_press->game_object()->set_active(m_press);
}