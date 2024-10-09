#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <functional>
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

    unsigned char depth() { return m_depth; }

    void set_depth(unsigned char depth);
    
    unsigned char chulling_mask() { return m_chulling_mask; }
    
    void set_chulling_mask(unsigned char chulling_mask);

    void clear();

    static void Foreach(std::function<void()> func);

    static Camera* current_camera() { return m_current_camera; }

    static void Sort();

    void SetOrthographic(float left, float right, float bottom, float top, float near, float far);

private:
    glm::mat4 m_view_mat4;
    glm::mat4 m_projection_mat4;
    glm::vec4 m_clear_color;
    unsigned int m_clear_flag;

    unsigned char m_depth;

    static std::vector<Camera*> m_cameras;
    static Camera* m_current_camera;

    unsigned char m_chulling_mask;

};




#endif // CAMERA_H