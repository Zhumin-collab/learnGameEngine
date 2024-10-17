//
// Created by yzm on 2024/10/17
//

#include "audio_studio_event.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "utils/debug.h"

AudioStudioEvent::AudioStudioEvent()
{
}

AudioStudioEvent::~AudioStudioEvent()
{
}

FMOD_RESULT
    AudioStudioEvent::SetParameterByName(const char *name, float value, bool ignoreseekspeed)
{
    return FMOD_Studio_EventInstance_SetParameterByName(m_event_instance, name, value, ignoreseekspeed);
}

FMOD_RESULT
    AudioStudioEvent::Set3DAttribute(float x, float y, float z)
{
    FMOD_3D_ATTRIBUTES pos = {{x, y, z}};
    return FMOD_Studio_EventInstance_Set3DAttributes(m_event_instance, &pos);
}

void AudioStudioEvent::Start()
{
    FMOD_RESULT result = FMOD_Studio_EventInstance_Start(m_event_instance);
    if(result!=FMOD_OK)
    {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Start failed:{}", int(result));
    }
}

void AudioStudioEvent::Pause()
{
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetPaused(m_event_instance, true);
    if(result!=FMOD_OK)
    {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_SetPaused failed:{}", int(result));
    }
}

void AudioStudioEvent::Stop()
{
    FMOD_RESULT result = FMOD_Studio_EventInstance_Stop(m_event_instance, FMOD_STUDIO_STOP_MODE::FMOD_STUDIO_STOP_IMMEDIATE);
    if(result!=FMOD_OK)
    {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Stop failed:{}", int(result));
    }
}