//
// created by yzm on 2024/09/21
//
#define RTTR_DLL
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/gl.h>
#include <rttr/registration>

#include "camera.h"
#include "component/game_object.h"
#include "component/transform.h"

RTTR_REGISTRATION
{
    rttr::registration::class_<Camera>("Camera")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

Camera::Camera():m_clear_color(49.f/255,77.f/255,121.f/255,1.f),m_clear_flag(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
{

}

Camera::~Camera()
{

}

void Camera::SetView(const glm::vec3& cameraForward, const glm::vec3& cameraUp)
{
    auto transform = dynamic_cast<Transform*>(game_object()->get_component("Transform"));
    m_view_mat4 = glm::lookAt(transform->position(), cameraForward, cameraUp);
}

void Camera::SetProjection(float fov, float aspect, float near, float far)
{
    m_projection_mat4 = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::clear()
{
    glClear(m_clear_flag);
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
}

