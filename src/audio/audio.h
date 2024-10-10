//
// created by yzm on 2024/10/10
//

#ifndef AUDIO_H
#define AUDIO_H

#include "fmod/api/core/inc/fmod.h"

class Audio{
public:
    /// @brief 初始化音频系统
    static void Init();

    /// @brief 创建音效
    /// @param name 
    /// @param mode 
    /// @param exinfo 
    /// @param sound 
    /// @return 
    static FMOD_RESULT CreateSound(const char* name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD_SOUND** sound);

    /// @brief 播放音效
    /// @param sound 
    /// @param channelgroup 
    /// @param paused 
    /// @param channel 
    /// @return 
    static FMOD_RESULT PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channelgroup, bool paused, FMOD_CHANNEL** channel);

    static FMOD_RESULT Update();

private:
    static FMOD_SYSTEM* m_fmod_system;



private:

};








#endif // AUDIO_H