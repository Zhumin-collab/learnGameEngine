//
// Created by yzm on 2024/10/16
//

#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include "component/component.h"
#include "audio_clip.h"

class AudioSource:public Component{

public:
    AudioSource();

    AudioClip* audio_clip(){return m_audio_clip;}
    void set_audio_clip(AudioClip* audio_clip){m_audio_clip = audio_clip;}

    void Set3DMode(bool mode_3d);

    void SetLoop(bool mode_loop);

    void Play();
    void Pause();
    void Stop();

    bool Paused();

private:
    void Update() override;


private:
    AudioClip* m_audio_clip;
    FMOD_CHANNEL* m_fmod_channel;
    FMOD_MODE m_fmod_mode = FMOD_DEFAULT;

};







#endif //AUDIO_SOURCE_H