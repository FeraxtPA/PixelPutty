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
     m_ScaleSpeed{ 0.0f }, 
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
    
    
    // Initialize obstacles with positions
    m_Obstacles.emplace_back();  
    m_Obstacles.back().SetPosition({ 200.0f, 200.0f });

    m_Obstacles.emplace_back();  
    m_Obstacles.back().SetPosition({ 400.0f, 300.0f });


    
}



Game::~Game()
{
    TextureManager::Unload();
}

void Game::Draw()
{
	m_Background.Draw();
	m_Hole.Draw();
    
    for (auto& obstacle : m_Obstacles)
    {
        obstacle.Draw();  
    }

	m_Ball.Draw();
  
}

void Game::Update(float deltaTime)
{
	m_Ball.Update(deltaTime);
	


    if (CheckBallAndHoleCollision())
    {
        m_Ball.SetSpeed(10.0f);
        m_IsInHole = true;
    }
    if(m_IsInHole)
    {
        BallAnimation(deltaTime);
    }

    if (CheckBallAndObstacleCollision())
    {
        ApplyCollisionResponse();
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
    return distance <= (holeRadius - ballRadius / 4.0f) && m_Ball.GetSpeed() < 500.0f;
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

void Game::ApplyCollisionResponse()
{
    if (m_CollisionPenetration > 0.0f)
    {
        //Small displacement so that the ball doesn's get stuck on the corner
        Vector2 displacement = {
            m_LastCollisionNormal.x * m_CollisionPenetration,
            m_LastCollisionNormal.y * m_CollisionPenetration
        };

        Vector2 newBallPos = m_Ball.GetPosition();
        newBallPos.x += displacement.x;
        newBallPos.y += displacement.y;
        m_Ball.SetPosition(newBallPos);

        // Reflect ball direction based on collision normal
        if (m_LastCollisionNormal.x != 0.0f) m_Ball.ReflectDirectionX();
        if (m_LastCollisionNormal.y != 0.0f) m_Ball.ReflectDirectionY();

        // Decrease the ball's speed to simulate energy loss
        m_Ball.DecreaseSpeed(0.8f); 

        // Reset collision data
        m_LastCollisionNormal = { 0.0f, 0.0f };
        m_CollisionPenetration = 0.0f;
    }

}

bool Game::CheckBallAndObstacleCollision()
{
    bool collisionDetected = false;
    for (auto& obstacle : m_Obstacles)
    {
        Vector2 ballPos = m_Ball.GetPosition();
        float ballRadius = m_Ball.GetRadius();
        Rectangle obstacleRect = obstacle.GetRect();

        if (CheckCollisionCircleRec(ballPos, ballRadius, obstacleRect))
        {
            // Calculate the penetration depth for each axis
            float dx = fmaxf(obstacleRect.x - ballPos.x, 0.0f) + fmaxf(ballPos.x - (obstacleRect.x + obstacleRect.width), 0.0f);
            float dy = fmaxf(obstacleRect.y - ballPos.y, 0.0f) + fmaxf(ballPos.y - (obstacleRect.y + obstacleRect.height), 0.0f);
            float penetrationDepthX = ballRadius - dx;
            float penetrationDepthY = ballRadius - dy;

            // Determine the collision normal based on penetration depths
            Vector2 collisionNormal = { 0.0f, 0.0f };
            if (penetrationDepthX < penetrationDepthY)
            {
                collisionNormal.x = (ballPos.x < obstacleRect.x + obstacleRect.width / 2) ? -1.0f : 1.0f;
            }
            else
            {
                collisionNormal.y = (ballPos.y < obstacleRect.y + obstacleRect.height / 2) ? -1.0f : 1.0f;
            }

            
            m_LastCollisionNormal = collisionNormal;
            m_CollisionPenetration = fminf(penetrationDepthX, penetrationDepthY);

            collisionDetected = true;
        }
    }

    return collisionDetected;
}







