#pragma once
#include "raylib.h"
#include "ball.h"
#include "background.h"
#include "hole.h"


class Game
{
	


public:

	Game(int width, int height);
	~Game();
	void Draw();
	void Update(float deltaTime);
	bool CheckBallAndHoleCollision();
	void BallAnimation(float deltaTime);

private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	Ball m_Ball;
	Hole m_Hole;
	Background m_Background;


    float m_ScaleDuration;    
	float m_ScaleSpeed;
    float m_TargetScale;  
	bool m_IsInHole;
};