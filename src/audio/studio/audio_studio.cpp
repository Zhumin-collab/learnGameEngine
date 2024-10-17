//
// Created by yzm on 2024/10/17
//


#include "audio_studio.h"
#include "utils/application.h"
#include "utils/debug.h"

FMOD_STUDIO_SYSTEM* AudioStudio::m_system = nullptr;

FMOD_RESULT AudioStudio::Init()
{
    FMOD_RESULT result = FMOD_Studio_System_Create(&m_system, FMOD_VERSION);
    if(result!=FMOD_OK)
    {
        return result;
    }

    result = FMOD_Studio_System_Initialize(m_system, 1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if(result!=FMOD_OK)
    {
        return result;
    }
    
    return FMOD_OK;

}

FMOD_RESULT AudioStudio::Update()
{
    if(m_system==nullptr)
    {
        return FMOD_ERR_INVALID_HANDLE;
    }
    return FMOD_Studio_System_Update(m_system);
}

FMOD_RESULT AudioStudio::loadBankFile(std::string file_name)
{
    std::string bank_path = Application::data_path() + file_name;
    FMOD_STUDIO_BANK* bank = nullptr;

    return FMOD_Studio_System_LoadBankFile(m_system, bank_path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
}

AudioStudioEvent* AudioStudio::CreateEventInstance(const char* event_path)
{
    FMOD_STUDIO_EVENTDESCRIPTION* event_desc = nullptr;
    FMOD_RESULT result = FMOD_Studio_System_GetEvent(m_system, event_path, &event_desc);

    if(result!=FMOD_OK)
    {
        DEBUG_LOG_ERROR("FMOD_Studio_System_GetEvent failed:{}", int(result));
        return nullptr;
    }

    FMOD_STUDIO_EVENTINSTANCE* event_instance = nullptr;
    result = FMOD_Studio_EventDescription_CreateInstance(event_desc, &event_instance);
    if(result!=FMOD_OK)
    {
        DEBUG_LOG_ERROR("FMOD_Studio_EventDescription_CreateInstance failed:{}", int(result));
        return nullptr;
    }

    AudioStudioEvent* audio_studio_event = new AudioStudioEvent();
    audio_studio_event->set_event_instance(event_instance);
    return audio_studio_event;
}

void AudioStudio::setListenerAttributes(float x, float y, float z)
{
    FMOD_3D_ATTRIBUTES pos = {{x, y, z}};
    pos.forward.z = 1.f;
    pos.up.y = 1.f;
    FMOD_Studio_System_SetListenerAttributes(m_system, 0, &pos, 0);
}