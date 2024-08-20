#pragma once
#include "raylib.h"
#include "math.h"
class Ball
{
public:
    Ball(int screenWidth, int screenHeight);
    ~Ball();
    void Draw();
    void Update(float deltaTime);
    void Move(float deltaTime);
    Vector2 GetPosition() { return m_Position; }
    float GetRadius() { return m_ScaledRadius; }
    float GetSpeed() { return m_Speed; }
    float GetScale() {return m_Scale;}
    void SetSpeed(float speed){m_Speed = speed;}
    void SetScale(float scale){m_Scale = scale;}
    void SetPosition(Vector2 position){m_Position = position;}
    void Reset(Vector2 position);
private:
    float m_Speed{ 0.0f };
    float m_Scale{};
    float m_DragLength{};
    float m_ScaledRadius{};
    Vector2 m_Position{};
    Vector2 m_Direction{ 1,1 };
    int m_ScreenWidth{};
    int m_ScreenHeight{};
    float m_Friction{ 0.95f };
    bool m_IsDragging{};
    Vector2 m_DragStart{};
    Vector2 m_MousePos{};

    Texture2D m_BallTexture{};
    Texture2D m_ArrowTexture{};
    float m_ArrowRotation{};
    Vector2 m_ArrowOrigin;

    float m_BallMass{ 0.5f };
    float m_RollingFrictionCoefficient{ 0.1f };
   
    

};