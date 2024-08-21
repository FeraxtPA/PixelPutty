#pragma once

#include "raylib.h"

class Obstacle
{
public:
    Obstacle();
    ~Obstacle();

    void Draw();
    Rectangle GetRect() const;
    void SetPosition(Vector2 position);
    Vector2 GetPosition() const;
    static void LoadTextures();
    static void UnloadTextures();
private:
   

    static Texture2D m_ObstacleTexture;
    Vector2 m_Position{};
};
