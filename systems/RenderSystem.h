#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "../core/System.h"
#include "../renderer/Renderer.h"
class RenderSystem : public System {
public:
    void render(Renderer&, float alpha);
};

#endif