#pragma once
#include "raylib.h"


class Hole
{

public:
	Hole(int width, int height);
	~Hole();
	void Draw();
	Vector2 GetPosition() { return m_Position; }
	float GetRadius() { return m_ScaledRadius; }

private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	float m_ScaledRadius{};
	Texture2D m_HoleTexture;
	Vector2 m_Position{};

};