#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include "component/component.h"
#include "control/input.h"

class Transform;
class Camera;
class Material;
class LoginScene : public Component
{
public:
    LoginScene() {};
    void Awake();
    void Update();

private:
    void CreateFishSoupPot();
    
    void CreateFont();

private:
    Transform* m_transform;

    Material* m_material;
    
    Transform* m_transform_camera1;
    Camera* m_camera_1;
    Transform* m_transform_camera2;
    Camera* m_camera_2;


    vec2_ushort m_last_mouse_position;

};



#endif // LOGIN_SCENE_H