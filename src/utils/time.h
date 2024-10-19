//
// Created by yzm on 2024/10/16
//

#ifndef TIME_H
#define TIME_H

#include <string>
#include <chrono>

class Time
{
public:
    Time();
    ~Time();

    static void Init();
    static void Update();

    static float TimeSinceStartup();

    static float deltaTime(){return m_delta_time;}

private:
    static std::chrono::system_clock::time_point m_startup_time;
    static float m_last_frame_time;
    static float m_delta_time;
};





#endif //TIME_H