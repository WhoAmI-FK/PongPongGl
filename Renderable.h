#pragma once
#include "Vector2D.h"
#include "RendererComponent.h"

class Renderable
{
public:
    RendererComponent* _renderer;

    virtual void init(){}
    virtual void update(){}
    virtual void draw(){}
    virtual ~Renderable(){}
}

class RenderableRec : public Renderable
{
    // we will be assuming that every object has transform for now
private:
    SDL_Rect m_srcRect;

}
