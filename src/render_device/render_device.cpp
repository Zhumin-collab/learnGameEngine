//
// created by yzm on 2024/10/7
//

#include "render_device.h"

RenderDevice* RenderDevice::m_instance;

void RenderDevice::Enable(RenderDevice::RenderState state)
{
    m_render_state_map[state] = true;
}

void RenderDevice::Disable(RenderDevice::RenderState state)
{
    m_render_state_map[state] = false;
}

void RenderDevice::Init(RenderDevice* instance)
{
    m_instance = instance;
}
