#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "Renderable.h"
#include <SDL.h>
#include "Constants.h"
#include "Application.h"

/*
inline ComponentID getNewRenderableTypeID()
{
	static RenderableID lastID = 0u;
	return lastID++;
}

template <typename T> inline RenderableID getRenderableTypeID() noexcept
{
	static_assert (std::is_base_of<Renderable, T>::value, "");
	static RenderableID typeID = getNewComponentTypeID();
	return typeID;
}
// TBD LATER
*/
class Renderable;

class RendererComponent : public Component
{
private:
    std::vector<std::unique_ptr<Renderable>> m_renderables;
    // TBD LATER
    //RenderableArray m_renderableArray;
    //RenderableBitSet m_renderableBitset;
public:
    TransformComponent* m_transformPtr; // TODO move to private, but then need to fix in renderable priv context
    RendererComponent() = default;
    ~RendererComponent();

	template <typename T, typename... TArgs>
	T& addRenderable(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->_renderer = this;
		std::unique_ptr<Renderable>uPtr { c };
		m_renderables.emplace_back(std::move(uPtr));

    // TBD LATER
	//	m_renderableArray[getRenderableTypeID<T>()] = c;
	//	m_renderableBitset[getRenderableTypeID<T>()] = true;

		c->init();
		return *c;
	}

    void init() override;
    void update() override;
    void render() override;
};

class Renderable
{
public:
    RendererComponent* _renderer;
    virtual void init(){}
    virtual void update(){}
    virtual void render(){}
    virtual ~Renderable(){}
};

class RenderableRec : public Renderable
{
    // we will be assuming that every object has transform for now
private:
    SDL_Rect m_srcRect;
public:
    void init() override {
        m_srcRect.x = m_srcRect.y = 0;
        m_srcRect.w = _renderer->m_transformPtr->m_width;
        m_srcRect.h = _renderer->m_transformPtr->m_height;
    }
    void update() override {
        m_srcRect.x = _renderer->m_transformPtr->m_position.x;
        m_srcRect.y = _renderer->m_transformPtr->m_position.y;
        m_srcRect.w = _renderer->m_transformPtr->m_width;
        m_srcRect.h = _renderer->m_transformPtr->m_height;
    }
    void render() override {
        SDL_SetRenderDrawColor(App::glb_renderer, 255,255,255,255);
	    SDL_RenderFillRect(App::glb_renderer, &m_srcRect);
	    SDL_SetRenderDrawColor(App::glb_renderer, 0, 0, 0, 255);
    }
};

class RenderableCircle : public Renderable
{
public:
    RenderableCircle(){};
};