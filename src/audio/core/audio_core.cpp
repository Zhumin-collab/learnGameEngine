//
// Created by yzm on 2024/10/17
//

#include "audio_core.h"
#include "utils/debug.h"

FMOD_SYSTEM* AudioCore::m_fmod_system = nullptr;

void AudioCore::Init()
{
    FMOD_RESULT result;
    
    result = FMOD_System_Create(&m_fmod_system,FMOD_VERSION);

    DEBUG_LOG_INFO("FMOD System Create result:{}", result);
    spdlog::info("FMOD System Create result:{}", result);

    unsigned int version;
    result = FMOD_System_GetVersion(m_fmod_system, &version);
    DEBUG_LOG_INFO("FMOD System Version:{}", version);

    if(version<FMOD_VERSION)
    {
        spdlog::critical("FMOD lib version is too old");
        return;
    }

    result = FMOD_System_Init(m_fmod_system, 32, FMOD_INIT_NORMAL, nullptr);
    DEBUG_LOG_ERROR("FMOD System Init result:{}", result);
}

FMOD_RESULT AudioCore::Update()
{
    if(m_fmod_system==nullptr)
    {
        return FMOD_ERR_INVALID_HANDLE;
    }
    return FMOD_System_Update(m_fmod_system);
}

FMOD_RESULT
AudioCore::CreateSound(const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *ex_info, FMOD_SOUND **sound)
{
    return FMOD_System_CreateSound(m_fmod_system, name_or_data, mode, ex_info, sound);
}

FMOD_RESULT
    AudioCore::PlaySound(FMOD_SOUND *sound, FMOD_CHANNELGROUP *channel_group, bool paused, FMOD_CHANNEL **channel)
{
    return FMOD_System_PlaySound(m_fmod_system, sound, channel_group, paused, channel);
}

FMOD_RESULT
    AudioCore::Set3DListenerAttributes(int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward,
                                       const FMOD_VECTOR *up)
{
    return FMOD_System_Set3DListenerAttributes(m_fmod_system, listener, pos, vel, forward, up);
}