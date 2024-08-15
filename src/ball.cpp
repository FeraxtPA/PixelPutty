#include "ball.h"

#include <raylib.h>
#include <iostream>

Ball::Ball(int screenWidth, int screenHeight)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;
  
    

    m_Position.x = static_cast<float>(m_ScreenWidth) / 2;
    m_Position.y = static_cast<float>(m_ScreenHeight) / 2; 
    m_IsDragging = false;

    m_BallTexture = LoadTexture("assets/ball.png");
    m_ScaledRadius = (m_BallTexture.width / 2.0f) * 5;

    m_ArrowTexture = LoadTexture("assets/arrow.png");
    m_ArrowOrigin = { m_ArrowTexture.width / 2.0f, m_ArrowTexture.height / 2.0f };
    
}

Ball::~Ball()
{
    UnloadTexture(m_BallTexture);
    UnloadTexture(m_ArrowTexture);
}

void Ball::Draw()
{

    //Vector2 drawPosition = { m_Position.x - (m_ScaledRadius / 5), m_Position.y - (m_ScaledRadius / 5) };
   //DrawCircle( m_Position.x,  m_Position.y, m_Radius+7, BLACK); //Imitate black outline
   //DrawCircle( m_Position.x,  m_Position.y, m_Radius, WHITE);
   
   DrawTextureEx(m_BallTexture,{ m_Position.x -m_ScaledRadius ,m_Position.y - m_ScaledRadius},0,5,WHITE);
   
   if (m_IsDragging)
    {
        

        //Offset arrow depending on its angle around the ball so the tail is always touching the ball
        Vector2 arrowPosition = {
            m_Position.x + m_ScaledRadius * cos((m_ArrowRotation * (PI/180))),
            m_Position.y + m_ScaledRadius * sin((m_ArrowRotation * (PI/180)))
        };

       
     
      
        DrawTexturePro(m_ArrowTexture, 
                       { 0, 0, (float)m_ArrowTexture.width, (float)m_ArrowTexture.height }, 
                       { arrowPosition.x, arrowPosition.y, (float)m_ArrowTexture.width * 6, (float)m_ArrowTexture.height * 5 },
                       { 0, m_ScaledRadius},  
                       m_ArrowRotation,  
                       WHITE);

        DrawLineEx({m_Position.x,m_Position.y}, {m_MousePos.x, m_MousePos.y}, 5, RED );
    }
}

void Ball::Move()
{
    
        float deltaTime = GetFrameTime();

        m_Position.x += m_Direction.x* m_Speed * deltaTime;
        m_Position.y += m_Direction.y*m_Speed * deltaTime;

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

        if(m_Speed > 0)
        {
         m_Speed -= m_Friction * deltaTime;
        }
        

        
        // Stop the ball completely if speed is too low
        if (m_Speed < 50.0f)  
        {
            m_Speed = 0.0f;
        }

    
}

void Ball::Update()
{
    m_MousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
        
        m_ArrowRotation = atan2(m_Position.y - m_MousePos.y,m_Position.x - m_MousePos.x) * (180/PI);
        // If the mouse button is released, calculate speed and direction
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector2 dragVector = { m_MousePos.x - m_DragStart.x, m_MousePos.y - m_DragStart.y };
            m_Speed = std::min(sqrt(dragVector.x * dragVector.x + dragVector.y * dragVector.y) * 5.0f, 3000.0f); // Adjust the multiplier as needed for game feel

            // Normalize the direction vector
            float length = sqrt(dragVector.x * dragVector.x + dragVector.y * dragVector.y);
            if (length > 0)
            {
                //Minus becase we need to send the ball
                //the opposite direction from the drag motion
                m_Direction.x = -dragVector.x / length;
                m_Direction.y = -dragVector.y / length;
            }

            m_IsDragging = false;
        }
    }
    else
    {
        Move();
    
    }
}

