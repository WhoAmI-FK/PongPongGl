#pragma once

#include "TransformComponent.h"
#include "Constants.h"

class BallController : public Component
{
public:
    TransformComponent *m_transform;
    GameObject* player_l;
    GameObject* player_r;

    BallController(GameObject* playerLeft, GameObject* playerRight)
    : player_l(playerLeft), player_r(playerRight)
    {

    }

    void init() override
    {
        m_transform = &m_gObjPtr->getComponent<TransformComponent>();
        m_transform->m_velocity.y = 1;
        m_transform->m_velocity.x = 1;
    }

    void update() override
    {        
        if(m_transform->m_position.y < 0) {
            VerticalBounce();
            m_transform->m_position.y = 0;
        }
        else if(m_transform->m_position.y + m_transform->m_radius > SCREEN_HEIGHT)
        {
            VerticalBounce();
            m_transform->m_position.y = static_cast<float>(SCREEN_HEIGHT - m_transform->m_radius);
        }

        if(m_transform->m_position.x < player_l->getComponent<TransformComponent>().m_width + m_transform->m_radius  +  player_l->getComponent<TransformComponent>().m_position.x)
        {
            float LPY = player_l->getComponent<TransformComponent>().m_position.y;
            if(m_transform->m_position.y >= LPY &&
               m_transform->m_position.y <= LPY + player_l->getComponent<TransformComponent>().m_height)
            {
                HorizontalBounce(true);
                m_transform->m_position.x = static_cast<float>(player_l->getComponent<TransformComponent>().m_width + m_transform->m_radius + player_l->getComponent<TransformComponent>().m_position.x);
            }
        }

        if(m_transform->m_position.x > player_r->getComponent<TransformComponent>().m_position.x - m_transform->m_radius)
        {
            float RPY = player_r->getComponent<TransformComponent>().m_position.y;
            if(m_transform->m_position.y >= RPY &&
               m_transform->m_position.y <= RPY + player_r->getComponent<TransformComponent>().m_height)
            {
                HorizontalBounce(false);
                m_transform->m_position.x = static_cast<float>(player_r->getComponent<TransformComponent>().m_position.x - m_transform->m_radius);
            }
        }
    }
  
    void VerticalBounce()
    {
        m_transform->m_velocity.y = -m_transform->m_velocity.y;
    }

    void HorizontalBounce(bool isLPadle)
    {
        const float PBOUNCE_MULT = 10.f;
        m_transform->m_velocity.x = -m_transform->m_velocity.x;
        if(isLPadle){
            // Process Left Paddle hits
            float lpaddle_center = player_l->getComponent<TransformComponent>().m_position.y + player_l->getComponent<TransformComponent>().m_height / 2; 
            m_transform->m_velocity.y = (m_transform->m_position.y - lpaddle_center) / player_l->getComponent<TransformComponent>().m_height / 2 * m_transform->m_speed * PBOUNCE_MULT;
        }else{
            // Process Right Paddle hits
            float rpaddle_center = player_r->getComponent<TransformComponent>().m_position.y + player_r->getComponent<TransformComponent>().m_height / 2; 
            m_transform->m_velocity.y = (m_transform->m_position.y - rpaddle_center) / player_r->getComponent<TransformComponent>().m_height / 2 * m_transform->m_speed * PBOUNCE_MULT;
        }
    }
};