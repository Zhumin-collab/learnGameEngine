//
// created by yzm on 2024/10/10
//

#include "audio.h"
#include "utils/debug.h"


FMOD_SYSTEM* Audio::m_fmod_system;

void Audio::Init()
{
    FMOD_RESULT result;
    result = FMOD_System_Create(&m_fmod_system,0);

    DEBUG_LOG_INFO("FMOD_System_Create result: {}", result);

    unsigned int version;
    result = FMOD_System_GetVersion(m_fmod_system, &version);
    DEBUG_LOG_INFO("FMOD_System_GetVersion result: {}", result);

    if(version < FMOD_VERSION)
    {
        DEBUG_LOG_ERROR("FMOD lib version is too old");
    }

    result = FMOD_System_Init(m_fmod_system, 32, FMOD_INIT_NORMAL, 0);

    DEBUG_LOG_INFO("FMOD_System_Init result: {}", result);


}

FMOD_RESULT Audio::Update(){
    return FMOD_System_Update(m_fmod_system);
}

FMOD_RESULT Audio::CreateSound(const char* name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD_SOUND** sound){
    DEBUG_LOG_INFO("Audio::CreateSound name:{}",name);
    return FMOD_System_CreateSound(m_fmod_system, name, mode, exinfo, sound);
}

FMOD_RESULT Audio::PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channelgroup, bool paused, FMOD_CHANNEL** channel){
    return FMOD_System_PlaySound(m_fmod_system, sound, channelgroup, paused, channel);
}