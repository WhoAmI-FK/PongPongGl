#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include <SDL.h>

class RendererComponent : public Component
{
private:
    TransformComponent* m_transformPtr;
    SDL_Rect m_srcRect;
public:
    RendererComponent() = default;
    ~RendererComponent();

    void init() override;
    void update() override;
    void render() override;

};
