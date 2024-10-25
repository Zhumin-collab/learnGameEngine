//
// Created by yzm on 2024/10/16
//

#include "audio_clip.h"
#include "utils/application.h"
#include "spdlog/spdlog.h"


AudioClip::AudioClip(){}

AudioClip::~AudioClip()
{
    if(m_fmod_sound!=nullptr)
    {
        FMOD_Sound_Release(m_fmod_sound);
        m_fmod_sound = nullptr;
    }
}

AudioClip* AudioClip::LoadFromFile(std::string audio_file_path)
{
    FMOD_SOUND* fmod_sound;
    FMOD_RESULT result = AudioCore::CreateSound((Application::data_path()+audio_file_path).c_str(), FMOD_DEFAULT, nullptr, &fmod_sound);

    if(result!=FMOD_OK)
    {
        spdlog::error("Load audio file failed:{}", audio_file_path);
        return nullptr;
    }

    AudioClip* audio_clip = new AudioClip();
    audio_clip->m_fmod_sound = fmod_sound;
    return audio_clip;
}


