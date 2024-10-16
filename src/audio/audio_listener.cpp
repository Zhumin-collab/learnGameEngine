//
// Created by yzm on 2024/10/16
//

#define RTTR_DLL
#include <rttr/registration>

#include "audio_listener.h"
#include "spdlog/spdlog.h"
#include "component/game_object.h"
#include "component/transform.h"


RTTR_REGISTRATION
{
    rttr::registration::class_<AudioListener>("AudioListener")
    .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

unsigned int AudioListener::m_listener_num = 0;

AudioListener::AudioListener():Component() {
    m_listener_id = m_listener_num++;
}

void AudioListener::Awake()
{
}

void AudioListener::Update()
{
    Component::Update();

    auto transform = dynamic_cast<Transform*>(game_object()->get_component("Transform"));
    if(transform==nullptr)
    {
        return;
    }

    auto pos = transform->position();
    FMOD_VECTOR audio_listener_pos = {pos.x, pos.y, pos.z};
    FMOD_VECTOR vel = {0.f, 0.f, 0.f};
    FMOD_VECTOR forward = {0.f, 0.f, 1.f};
    FMOD_VECTOR up = {0.f, 1.f, 0.f};

    FMOD_RESULT result = Audio::Set3DListenerAttributes(m_listener_id, &audio_listener_pos, &vel, &forward, &up);
}