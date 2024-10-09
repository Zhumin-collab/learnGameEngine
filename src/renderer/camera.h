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

    /// @brief 设置正交相机矩阵
    /// @param left 
    /// @param right 
    /// @param bottom 
    /// @param top 
    /// @param z_near
    /// @param z_far
    void SetOrthographic(float left, float right, float bottom, float top, float near, float far);

    /// @brief 设置清屏颜色
    /// @param r 
    /// @param g 
    /// @param b 
    /// @param a 
    void set_clear_color(float r, float g, float b, float a) { m_clear_color = glm::vec4(r,g,b,a); }

    /// @brief 设置刷帧内容种类
    /// @param clear_flag 
    void set_clear_flag(unsigned int clear_flag) { m_clear_flag = clear_flag; }
    
    /// @brief 清屏
    void clear();

    /// @brief 获得深度
    /// @return 
    unsigned char depth() { return m_depth; }

    void set_depth(unsigned char depth);
    
    unsigned char chulling_mask() { return m_chulling_mask; }
    
    void set_chulling_mask(unsigned char chulling_mask);


    enum CameraUseFor{
        UI,
        SCENE
    };

    CameraUseFor camera_use_for(){ return m_camera_use_for; }

protected:
    glm::mat4 m_view_mat4;
    glm::mat4 m_projection_mat4;
    glm::vec4 m_clear_color;
    unsigned int m_clear_flag;

    unsigned char m_depth;

    unsigned char m_chulling_mask;

    CameraUseFor m_camera_use_for = CameraUseFor::SCENE;

public:
    static void Sort();

    static void Foreach(std::function<void()> func);

    static Camera* current_camera(){return m_current_camera;}

private:


    static std::vector<Camera*> m_cameras;
    static Camera* m_current_camera;


};




#endif // CAMERA_H