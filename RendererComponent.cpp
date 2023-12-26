#include "RendererComponent.h"
#include "Application.h"

RendererComponent::~RendererComponent()
{

}

void RendererComponent::init() {
    m_transformPtr = &m_gObjPtr->getComponent<TransformComponent>();
    m_srcRect.x = m_srcRect.y = 0;
    m_srcRect.w = m_transformPtr->m_width;
    m_srcRect.h = m_transformPtr->m_height;
}

void RendererComponent::update() {
    m_srcRect.x = m_transformPtr->m_position.x;
    m_srcRect.y = m_transformPtr->m_position.y;
    m_srcRect.w = m_transformPtr->m_width;
    m_srcRect.h = m_transformPtr->m_height;
}

void RendererComponent::render()
{
    SDL_SetRenderDrawColor(App::glb_renderer, 255,255,255,255);
	SDL_RenderFillRect(App::glb_renderer, &m_srcRect);
	SDL_SetRenderDrawColor(App::glb_renderer, 0, 0, 0, 255);
}
