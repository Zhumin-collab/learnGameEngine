//
// Created by yzm on 2024/10/16
//

#include "time.h"

std::chrono::system_clock::time_point Time::m_startup_time;
float Time::m_delta_time = 0;
float Time::m_last_frame_time = 0;

Time::Time()
{

}

Time::~Time()
{

}

void Time::Init()
{
    m_startup_time = std::chrono::system_clock::now();
}

void Time::Update()
{
    if(m_last_frame_time > 0){
        m_delta_time = TimeSinceStartup() - m_last_frame_time;
    }
    m_last_frame_time = TimeSinceStartup();
}

float Time::TimeSinceStartup()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startup_time).count();
    return ms/1000.f;
}