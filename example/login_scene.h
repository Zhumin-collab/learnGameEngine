#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include "component/component.h"
#include "control/input.h"
#include "audio/audio.h"
class Transform;
class Camera;
class Material;
class LoginScene : public Component
{
public:
    LoginScene():Component() {};
    void Awake();
    void Update();

private:
    void CreateFishSoupPot();
    
    void CreateQuad();

    void CreateSounds();

    void PlayPauseSound(FMOD_SOUND* sound,FMOD_CHANNEL** channel);
private:
    Transform* m_transform;

    Material* m_material;
    
    Transform* m_transform_camera1;
    Camera* m_camera_1;
    Transform* m_transform_camera2;
    Camera* m_camera_2;


    glm::vec2 m_last_mouse_position;

    FMOD_SOUND     *m_sound_1= nullptr, *m_sound_2= nullptr, *m_sound_3= nullptr;
    FMOD_CHANNEL   *m_channel_1= nullptr, *m_channel_2= nullptr, *m_channel_3= nullptr;

};



#endif // LOGIN_SCENE_H