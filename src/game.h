#pragma once
#include "raylib.h"
#include "ball.h"
#include "background.h"
#include "hole.h"
#include "obstacle.h"
#include <vector>
#include "TextureManager.h"
#include "ui.h"

class Game
{
	


public:

	Game(int width, int height);
	~Game();
	void Draw();
	void Update(float deltaTime);
	bool CheckBallAndHoleCollision();
	bool CheckBallAndObstacleCollision();
	void BallAnimation(float deltaTime);
	
	void ApplyCollisionResponse();
private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	

	Ball m_Ball;
	Hole m_Hole;
	Background m_Background;
	UI m_UI;
	std::vector<Obstacle> m_Obstacles;

	float m_ScaleDuration{};
	float m_ScaleSpeed{};
    float m_TargetScale{};
	bool m_IsInHole{};
	Vector2 m_LastCollisionNormal{};
	float m_CollisionPenetration{};
	bool m_IsInitialized{};
};