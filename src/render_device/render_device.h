//
// created by yzm on 2024/10/7
//

#ifndef RENDER_DEVICE_H
#define RENDER_DEVICE_H

#include <unordered_map>

class RenderDevice
{
public:
    enum RenderState{
        None = 0,
        STENCIL_TEST
    };

public:
    virtual void Enable(RenderState state);
    virtual void Disable(RenderState state);

protected:
    std::unordered_map<RenderState, bool> m_render_state_map;

public:
    static void Init(RenderDevice* instance);

    static RenderDevice* instance() { return m_instance; };

private:
    static RenderDevice* m_instance;

};


#endif // RENDER_DEVICE_H