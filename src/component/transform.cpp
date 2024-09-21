//
// created by yzm on 2024/9/21
//
#define RTTR_DLL

#include "transform.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<Transform>("Transform")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr)
        .property("position", &Transform::position, &Transform::set_position)
        .property("rotation", &Transform::rotation, &Transform::set_rotation)
        .property("scale", &Transform::scale, &Transform::set_scale);
}

Transform::Transform():m_position(0.0f), m_rotation(0.0f), m_scale(1.0f) {

}

Transform::~Transform() {

}