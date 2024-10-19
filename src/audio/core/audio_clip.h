//
// Created by yzm on 2024/10/16
//

#ifndef AUDIO_CLIP_H
#define AUDIO_CLIP_H

#include "audio_core.h"
#include <string>

class AudioClip{

public:
    AudioClip();
    ~AudioClip();

    FMOD_SOUND* fmod_sound(){return m_fmod_sound;}

public:
    /// @brief 加载音效文件 创建AudioClip对象
    /// @param audio_file_path 
    /// @return 
    static AudioClip* LoadFromFile(std::string audio_file_path);

private:
    FMOD_SOUND* m_fmod_sound;



};








#endif //AUDIO_CLIP_H