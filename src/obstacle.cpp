#include "obstacle.h"
#include <iostream>


Texture2D Obstacle::m_ObstacleTexture{};

Obstacle::Obstacle()
{
    LoadTextures();
}

Obstacle::~Obstacle()
{
    
}

void Obstacle::Draw()
{
    DrawTextureEx(m_ObstacleTexture, m_Position, 0, 10, WHITE);
}

Rectangle Obstacle::GetRect() const
{
    Rectangle rect;
    rect.x = m_Position.x;
    rect.y = m_Position.y;
    rect.width = static_cast<float>(m_ObstacleTexture.width) * 10;
    rect.height = static_cast<float>(m_ObstacleTexture.height) * 10;
    return rect;
}

void Obstacle::SetPosition(Vector2 position)
{
    m_Position = position;
}

Vector2 Obstacle::GetPosition() const
{
    return m_Position;
}

void Obstacle::LoadTextures()
{
    if (m_ObstacleTexture.id == 0)
    {
        m_ObstacleTexture = LoadTexture("assets/obstacle.png");
    }
}

void Obstacle::UnloadTextures()
{
    if (m_ObstacleTexture.id != 0) 
    {
        UnloadTexture(m_ObstacleTexture);
        m_ObstacleTexture.id = 0; 
    }
}
