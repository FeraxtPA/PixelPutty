#include "ball.h"

#include <raylib.h>
#include <iostream>
#include "TextureManager.h"

Ball::Ball(int screenWidth, int screenHeight)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;

    m_BallTexture = TextureManager::GetTexture(0, 0);
    m_ArrowTexture = TextureManager::GetTexture(1, 0);
    m_Position.x = static_cast<float>(m_ScreenWidth) / 2;
    m_Position.y = static_cast<float>(m_ScreenHeight) / 2;
    m_IsDragging = false;

    

    float scaleFactor = 4.0f;
    m_ScaledRadius = (m_BallTexture.width / 2.0f) * scaleFactor;


    m_ArrowOrigin = { m_ArrowTexture.width / 2.0f, m_ArrowTexture.height / 2.0f };
    m_DragLength = 1.0f;

    m_Scale = 1.0f;

    m_IsActive = false;
}

Ball::~Ball()
{
    
}

void Ball::Draw()
{

    

    if (m_IsDragging)
    {
       
        //Offset arrow depending on its angle around the ball so the tail is always touching the ball
        Vector2 arrowPosition = {
            m_Position.x  + (m_ScaledRadius-5) * cos((m_ArrowRotation * (PI / 180))),
            m_Position.y  + (m_ScaledRadius-5) * sin((m_ArrowRotation * (PI / 180)))
        };

        DrawTexturePro(m_ArrowTexture,
            { 0, 0, (float)m_ArrowTexture.width, (float)m_ArrowTexture.height },
            { arrowPosition.x, arrowPosition.y, (float)m_ArrowTexture.width * 6, (float)m_ArrowTexture.height * 4},
            { 0, m_ScaledRadius },
            m_ArrowRotation,
            WHITE);

        DrawLineEx({ m_Position.x,m_Position.y }, { m_MousePos.x, m_MousePos.y }, 5, RED);
    }
        
    DrawTextureEx(m_BallTexture, { m_Position.x - m_ScaledRadius * m_Scale ,m_Position.y - m_ScaledRadius * m_Scale }, 0, 4 * m_Scale, WHITE);
}

void Ball::Move(float deltaTime)
{

    m_IsActive = true; // So that user can't click the ball when it's moving


    m_Position.x += m_Direction.x * m_Speed * deltaTime;
    m_Position.y += m_Direction.y * m_Speed * deltaTime;


    // Check for collisions and handle bouncing
    if (m_Position.x >= m_ScreenWidth - m_ScaledRadius)
    {
        m_Direction.x *= -1;
        m_Position.x = m_ScreenWidth - m_ScaledRadius;  // Clamp position
    }
    else if (m_Position.x <= m_ScaledRadius)
    {
        m_Direction.x *= -1;
        m_Position.x = m_ScaledRadius;  // Clamp position
    }

    if (m_Position.y >= m_ScreenHeight - m_ScaledRadius)
    {
        m_Direction.y *= -1;
        m_Position.y = m_ScreenHeight - m_ScaledRadius;  // Clamp position
    }
    else if (m_Position.y <= m_ScaledRadius)
    {
        m_Direction.y *= -1;
        m_Position.y = m_ScaledRadius;  // Clamp position
    }

    // Normal force = m_BallMass * g
    float rollingFriction = m_RollingFrictionCoefficient * m_BallMass * 9.81f; 
    float decayFactor = exp(-rollingFriction * deltaTime / m_BallMass);

    m_Speed *= decayFactor;


    if (m_Speed < 100.0f) // Using a small threshold to stop the ball
    {
        m_Speed = 0.0f;
        m_IsActive = false;
    }

}

void Ball::Reset(Vector2 position)
{
    m_Speed = 0.0f;
    m_Scale = 1.0f;
    m_Position = position;
}

void Ball::DecreaseSpeed(float factor)
{
    m_Speed *= factor;
}

void Ball::ReflectDirectionX()
{
    m_Direction.x *= -1;
}

void Ball::ReflectDirectionY()
{
    m_Direction.y *= -1;
}

void Ball::Update(float deltaTime)
{
    m_MousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_IsActive)
    {

        if (CheckCollisionPointCircle(m_MousePos, m_Position, m_ScaledRadius))
        {
            m_IsDragging = true;
            m_DragStart = m_Position;
        }
    }


    if (m_IsDragging)
    {
        m_MousePos = GetMousePosition();

        m_ArrowRotation = atan2(m_Position.y - m_MousePos.y, m_Position.x - m_MousePos.x) * (180 / PI);

        // If the mouse button is released, calculate speed and direction
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector2 dragVector = { m_MousePos.x - m_DragStart.x, m_MousePos.y - m_DragStart.y };
            m_Speed = std::min(sqrt(dragVector.x * dragVector.x + dragVector.y * dragVector.y) * 5.0f, 3000.0f); // Adjust the multiplier as needed for game feel
            
            // Normalize the direction vector
            m_DragLength = sqrt(dragVector.x * dragVector.x + dragVector.y * dragVector.y);
            
            if (m_DragLength > 0)
            {
                //Minus becase we need to send the ball
                //the opposite direction from the drag motion
                m_Direction.x = -dragVector.x / m_DragLength;
                m_Direction.y = -dragVector.y / m_DragLength;
            }

            m_IsDragging = false;
        }
    }
    else
    {
        Move(deltaTime);

    }
}
