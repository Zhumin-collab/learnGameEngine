//
// Created by yzm on 2024/10/17
//

#ifndef AUDIO_CORE_H
#define AUDIO_CORE_H

#include "fmod/api/core/inc/fmod.h"
#include "fmod/api/studio/inc/fmod_studio.h"

class AudioStudioEvent{

public:
    AudioStudioEvent();
    ~AudioStudioEvent();

    FMOD_STUDIO_EVENTINSTANCE* event_instance(){return m_event_instance;}
    void set_event_instance(FMOD_STUDIO_EVENTINSTANCE* event_instance){m_event_instance = event_instance;}

    FMOD_RESULT SetParameterByName(const char* name, float value, bool ignoreseekspeed=false);

    FMOD_RESULT Set3DAttribute(float x,float y,float z);

    void Start();

    void Stop();

    void Pause();

    


private:
    FMOD_STUDIO_EVENTINSTANCE* m_event_instance;

};



#endif //AUDIO_CORE_H