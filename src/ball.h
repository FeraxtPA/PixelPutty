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
    Vector2 GetPosition() const { return m_Position; }
    float GetRadius() const { return m_ScaledRadius; }
    float GetSpeed() const  { return m_Speed; }
    float GetScale() const {return m_Scale;}
    void SetSpeed(float speed){m_Speed = speed;}
    void SetScale(float scale){m_Scale = scale;}
    void SetPosition(Vector2 position){m_Position = position;}
    void Reset(Vector2 position);
    Vector2 GetDirection() const { return m_Direction; }
    void DecreaseSpeed(float factor);
    void ReflectDirectionX();
    void ReflectDirectionY();

private:
    void DrawPowerBar();
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
    bool m_IsActive{};
    Vector2 m_DragStart{};
    Vector2 m_MousePos{};

    Texture2D m_BallTexture{};
    Texture2D m_ArrowTexture{};
    Texture2D m_PowerBarFillTexture{};

    float m_ArrowRotation{};
    Vector2 m_ArrowOrigin;

    float m_BallMass{ 0.5f };
    float m_RollingFrictionCoefficient{ 0.1f };
   
    struct PowerBar
    {
        Color m_Red{177,62,83,255};
        Color m_Yellow{255,205,117,255};
        Color m_Green{ 37,113,121,255 };
        Color m_LightGreen{167,240,112,255};
        Color m_Black{ 26,28,44,255 };
    };

};