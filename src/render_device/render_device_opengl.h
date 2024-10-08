//
// created by yzm on 2024/10/7
//

#ifndef RENDER_DEVICE_OPENGL_H
#define RENDER_DEVICE_OPENGL_H

#include "render_device.h"

class RenderDeviceOpenGL : public RenderDevice
{
public:
    void Enable(RenderState state) override;
    void Disable(RenderState state) override;
};

#endif // RENDER_DEVICE_OPENGL_H