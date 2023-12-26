#include "TransformComponent.h"

TransformComponent::TransformComponent() : 
     m_height(32), m_width(32),
     m_scale(1),   m_speed(3),
     m_radius(0) // only for circle-like objs
{
    m_position.Zero();
}

TransformComponent::TransformComponent(int scale) :
    m_height(32), m_width(32),
    m_scale(scale), m_speed(3),
    m_radius(0)
{
    m_position.Zero();
}

TransformComponent::TransformComponent(float x, float y) :
     m_height(32), m_width(32),
     m_scale(1),   m_speed(3),
     m_radius(0)
{
    m_position.Zero();
    m_position.x = x;
    m_position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int scale)
    : m_height(h), m_width(w),
      m_scale(scale), m_speed(3),
      m_radius(0)
{
    m_position.Zero();
    m_position.x = x;
    m_position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int r)
    : m_radius(r)
{
    m_position.Zero();
    m_position.x = x;
    m_position.y = y;
}

void TransformComponent::init() 
{
    m_velocity.Zero();
}

void TransformComponent::update()
{
	m_position.x += static_cast<int>(m_velocity.x * m_speed);
	m_position.y += static_cast<int>(m_velocity.y * m_speed);
}