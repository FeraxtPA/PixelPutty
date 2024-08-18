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
	void Update();
	bool CheckBallAndHoleCollision();

private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	Ball m_Ball;
	Hole m_Hole;
	Background m_Background;
};