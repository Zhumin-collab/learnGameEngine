//
// Created by yzm on 2024/10/17
//

#ifndef AUDIO_STUDIO_H
#define AUDIO_STUDIO_H

#include <iostream>
#include "fmod/api/core/inc/fmod.h"
#include "fmod/api/studio/inc/fmod_studio.h"
#include "audio_studio_event.h"

class AudioStudio{
public:
    static FMOD_RESULT Init();

    static FMOD_RESULT Update();

    static FMOD_RESULT loadBankFile(std::string file_name);

    static AudioStudioEvent* CreateEventInstance(const char* event_path);

    static void setListenerAttributes(float x, float y, float z);

private:
    static FMOD_STUDIO_SYSTEM* m_system;
};

#endif //AUDIO_STUDIO_H