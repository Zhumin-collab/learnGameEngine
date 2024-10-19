//
// Created by yzm on 2024/10/17
//

#ifndef AUDIO_CORE_H
#define AUDIO_CORE_H

#include "fmod/api/core/inc/fmod.h"

class AudioCore{
public:
    static void Init();

    static FMOD_RESULT CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* ex_info, FMOD_SOUND **sound);

    static FMOD_RESULT PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group, bool paused, FMOD_CHANNEL** channel);

    static FMOD_RESULT Update();

    static FMOD_RESULT Set3DListenerAttributes(int listener, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel, const FMOD_VECTOR* forward, const FMOD_VECTOR* up);

private:
    static FMOD_SYSTEM* m_fmod_system;
};





#endif //AUDIO_CORE_H