#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include "component/component.h"

class Camera: public Component
{
public:
    Camera();
    ~Camera();

    void SetView(const glm::vec3& cameraForward, const glm::vec3& cameraUp);

    /// @brief 设置相机视野
    /// @param fov 相机朝前方向
    /// @param aspect 宽高比
    /// @param near 近裁剪面
    /// @param far 远裁剪面
    void SetProjection(float fov, float aspect, float near, float far);
    
    glm::mat4& view_mat4() { return m_view_mat4; }
    glm::mat4& projection_mat4() { return m_projection_mat4; }

    void set_clear_color(float r, float g, float b, float a) { m_clear_color = glm::vec4(r,g,b,a); }

    void set_clear_flag(unsigned int clear_flag) { m_clear_flag = clear_flag; }

    void clear();
private:
    glm::mat4 m_view_mat4;
    glm::mat4 m_projection_mat4;
    glm::vec4 m_clear_color;
    unsigned int m_clear_flag;

};




#endif // CAMERA_H