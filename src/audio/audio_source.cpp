//
// Created by yzm on 2024/10/16
//


#define RTTR_DLL
#include "audio_source.h"
#include <rttr/registration>
#include "spdlog/spdlog.h"
#include "component/game_object.h"
#include "component/transform.h"



RTTR_REGISTRATION
{
    rttr::registration::class_<AudioSource>("AudioSource")
    .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

AudioSource::AudioSource():Component() {}

void AudioSource::Set3DMode(bool mode_3d)
{
    if(mode_3d)
    {
        m_fmod_mode |= FMOD_3D;
    }
    else if(m_fmod_mode & FMOD_3D)
    {
        m_fmod_mode ^= FMOD_3D;
    }

    FMOD_RESULT result = FMOD_Channel_SetMode(m_fmod_channel, m_fmod_mode);
    if(result!=FMOD_OK)
    {
        spdlog::error("FMOD_Channel_SetMode failed:{}", int(result));
    }
}

void AudioSource::Play()
{
    if(m_audio_clip==nullptr)
    {
        spdlog::error("AudioSource::Play audio_clip is nullptr");
        return;
    }

    if(m_audio_clip->fmod_sound()==nullptr)
    {
        spdlog::error("AudioSource::Play fmod_sound is nullptr");
        return;
    }

    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    result = FMOD_Channel_GetPaused(m_fmod_channel, &paused);

    switch(result){
        case FMOD_OK:
            if(paused)
            {
                result = FMOD_Channel_SetPaused(m_fmod_channel, false);
            }
            break;
        case FMOD_ERR_INVALID_PARAM:
        case FMOD_ERR_INVALID_HANDLE:
        case FMOD_ERR_CHANNEL_STOLEN:
            result = Audio::PlaySound(m_audio_clip->fmod_sound(), nullptr, false, &m_fmod_channel);
            break;
        default:
            break;
    }
}

void AudioSource::Pause()
{
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    result = FMOD_Channel_GetPaused(m_fmod_channel, &paused);

    if(result==FMOD_OK)
    {
        if(!paused)
        {
            result = FMOD_Channel_SetPaused(m_fmod_channel, true);
        }
        return;
    }

    spdlog::error("FMOD_Channel_GetPaused failed:{}", int(result));
}

void AudioSource::Stop(){
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    result = FMOD_Channel_Stop(m_fmod_channel);
    if(result==FMOD_OK)
    {
        return;
    }
    spdlog::error("FMOD_Channel_Stop failed:{}", int(result));
}

bool AudioSource::Paused()
{
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    
    result = FMOD_Channel_GetPaused(m_fmod_channel, &paused);
    if(result==FMOD_OK)
    {
        return paused;
    }

    spdlog::error("FMOD_Channel_GetPaused failed:{}", int(result));
    return true;
}

void AudioSource::SetLoop(bool mode_loop)
{
    if(mode_loop){
        m_fmod_mode |= FMOD_LOOP_NORMAL;
    }else if(m_fmod_mode & FMOD_LOOP_NORMAL){
        m_fmod_mode ^= FMOD_LOOP_NORMAL;
    }

    FMOD_RESULT result = FMOD_Channel_SetMode(m_fmod_channel, m_fmod_mode);
    if(result!=FMOD_OK)
    {
        spdlog::error("FMOD_Channel_SetMode failed:{}", int(result));
    }
}

void AudioSource::Update()
{
    Component::Update();

    if(m_fmod_mode^FMOD_3D){
        auto transform = dynamic_cast<Transform*>(game_object()->get_component("Transform"));
        if(!transform)
        {
            return;
        }

        auto pos = transform->position();
        FMOD_VECTOR audio_source_pos = {pos.x, pos.y, pos.z};
        FMOD_VECTOR vel = {0.f, 0.f, 0.f};
        FMOD_Channel_Set3DAttributes(m_fmod_channel, &audio_source_pos, &vel);
    }
}