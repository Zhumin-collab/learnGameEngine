//
// created by yzm on 2024/10/7
//

#include <glad/gl.h>

#include "render_device_opengl.h"
#include "utils/debug.h"

void RenderDeviceOpenGL::Enable(RenderState state)
{
    if(m_render_state_map.find(state)!=m_render_state_map.end() && m_render_state_map[state])
    {
        return;
    }

    switch(state){
        case None:
            break;
        case STENCIL_TEST:
            glEnable(GL_STENCIL_TEST);
            break;

    }__CHECK_GL_ERROR__

    RenderDevice::Enable(state);
}

void RenderDeviceOpenGL::Disable(RenderState state)
{
    if(m_render_state_map.find(state)!=m_render_state_map.end()&&!m_render_state_map[state])
    {
        return;
    }

    switch(state)
    {
        case None:
            break;
        case STENCIL_TEST:
            glDisable(GL_STENCIL_TEST);
            break;
    }__CHECK_GL_ERROR__
    RenderDevice::Disable(state);
}
