//
// created by yzm on 2024/10/9
//

#define RTTR_DLL

#include "ui_camera.h"

#include <rttr/registration>

RTTR_REGISTRATION{
    rttr::registration::class_<UICamera>("UICamera")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UICamera::UICamera():Camera()
{
    m_camera_use_for = CameraUseFor::UI;
}