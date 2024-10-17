//
// Created by yzm on 2024/10/16
//

#ifndef AUDIO_LISTENER_H
#define AUDIO_LISTENER_H

#include "component/component.h"
#include "audio_clip.h"

class AudioListener:public Component{
public:
    AudioListener();

    virtual void Awake();
    virtual void Update();

private:
    unsigned int m_listener_id = 0;
    static unsigned int m_listener_num; //已经创建的listener

};








#endif //AUDIO_LISTENER_H