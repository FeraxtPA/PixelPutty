#include "game.h"
#include "math.h"
#include <iostream>


Game::Game(int width, int height)
   : m_ScreenWidth{ width },
     m_ScreenHeight{ height },
     m_Ball{ m_ScreenWidth, m_ScreenHeight },
     m_Hole{ m_ScreenWidth, m_ScreenHeight },
     m_Background{ m_ScreenWidth, m_ScreenHeight },
     m_ScaleDuration{ 1.0f }, // Duration in seconds to scale down
     m_ScaleSpeed{ 0.0f }, // This will be calculated
     m_TargetScale{ 0.1f },
     m_IsInHole{ false }
{
    // Calculate scale speed to reach target scale in m_ScaleDuration seconds
    float initialScale = m_Ball.GetScale();
    float scaleDifference = initialScale - m_TargetScale;
    if (scaleDifference > 0.0f)
    {
        m_ScaleSpeed = scaleDifference / m_ScaleDuration;
    }
}


Game::~Game()
{


}

void Game::Draw()
{
	m_Background.Draw();
	m_Hole.Draw();
	m_Ball.Draw();
}

void Game::Update(float deltaTime)
{
	m_Ball.Update(deltaTime);
	


    if (CheckBallAndHoleCollision())
    {
        m_Ball.SetSpeed(0.0f);
        m_IsInHole = true;
    }
    if(m_IsInHole)
    {
        BallAnimation(deltaTime);
    }

  
}

bool Game::CheckBallAndHoleCollision()
{
    Vector2 ballPos = m_Ball.GetPosition();
    Vector2 holePos = m_Hole.GetPosition();

    float ballRadius = m_Ball.GetRadius();
    float holeRadius = m_Hole.GetRadius();

    //Calculate center of hole since 0,0 is top left
    Vector2 holeCenterPos = {
        holePos.x + holeRadius,  

        holePos.y + holeRadius   
    };

    // Distance between the ball and the hole center

    float distance = sqrtf((ballPos.x - holeCenterPos.x) * (ballPos.x - holeCenterPos.x) +
        (ballPos.y - holeCenterPos.y) * (ballPos.y - holeCenterPos.y));



    //Check if ball is sufficiently in the hole at least 1/3+-
    return distance <= (holeRadius - ballRadius / 1.5f) && m_Ball.GetSpeed() < 500.0f;
}

void Game::BallAnimation(float deltaTime)
{
    
    // Update the ball's scale to shrink it
    float currentScale = m_Ball.GetScale();
    currentScale -= m_ScaleSpeed * deltaTime;

   
    if (currentScale < m_TargetScale)
    {
        currentScale = m_TargetScale;
    }
    
    m_Ball.SetScale(currentScale);

    if (currentScale <= m_TargetScale)
    {
        m_IsInHole = false;
        m_Ball.Reset({ static_cast<float>(m_ScreenWidth) / 2, static_cast<float>(m_ScreenHeight) / 2 });
    }
}

