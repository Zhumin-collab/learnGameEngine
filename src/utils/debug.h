#ifndef DEBUG_H
#define DEBUG_H


#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

#define DEBUG_LOG_INFO SPDLOG_INFO
#define DEBUG_LOG_WARN SPDLOG_WARN
#define DEBUG_LOG_ERROR SPDLOG_ERROR

#define __CHECK_GL_ERROR__ {\
    GLenum err = glGetError();\
    if (err != GL_NO_ERROR) {\
        DEBUG_LOG_ERROR("OpenGL error: {}", err);\
    }\
}

class Debug{
    public:
        static void Init();
};

#endif