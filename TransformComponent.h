#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D m_position;
    Vector2D m_velocity;

    int m_height;
    int m_width;
    int m_scale;
    int m_speed;
    int m_radius;

    TransformComponent();
    TransformComponent(int scale);
    TransformComponent(float x, float y);
    TransformComponent(float x, float y, int h, int w, int scale);

    void init() override;
    void update() override;
};
