#pragma once

#include "raylib.h"

class Obstacle
{
public:
    Obstacle();
    Obstacle(Texture2D texture); 
    ~Obstacle();

    void Draw();
    Rectangle GetRect() const;
    void SetPosition(Vector2 position);
    Vector2 GetPosition() const;
    void SetTexture(Texture2D texture); 

private:
    Vector2 m_Position{};
    Texture2D m_ObstacleTexture;
};
