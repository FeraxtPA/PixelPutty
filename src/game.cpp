#include "game.h"
#include "math.h"
#include <iostream>

Game::Game(int width, int height)
   :m_ScreenWidth{ width },
	m_ScreenHeight{ height },
	m_Ball{ m_ScreenWidth ,m_ScreenHeight },
	m_Hole{ m_ScreenWidth ,m_ScreenHeight },
	m_Background{ m_ScreenWidth ,m_ScreenHeight }
{
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

void Game::Update()
{
	m_Ball.Update();
	
   
    if (CheckBallAndHoleCollision() && m_Ball.GetSpeed() < 500.0f)
    {
        std::cerr << "Slow enough\n, You're in (:";
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
    return distance <= (holeRadius - ballRadius / 1.5f);
}


