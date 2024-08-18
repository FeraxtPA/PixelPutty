#include "hole.h"

Hole::Hole(int width,  int height)
{
	m_ScreenWidth  =  width;
	m_ScreenHeight =  height;

	m_HoleTexture = LoadTexture("assets/hole.png");
	float scaleFactor = 6.0f;
	m_Position = {
	   static_cast<float>((m_ScreenWidth - m_HoleTexture.width * scaleFactor) / 2),  // Center X with scaling
	   static_cast<float>(m_ScaledRadius + 100)  // Center Y at the top, accounting for the ball's radius
	};

	// Adjust the scaled radius based on the scaling factor
	m_ScaledRadius = (m_HoleTexture.width / 2.0f) * scaleFactor;
	
}

Hole::~Hole()
{
	UnloadTexture(m_HoleTexture);
}

void Hole::Draw()
{
	DrawTextureEx(m_HoleTexture, { m_Position.x , m_Position.y}, 0, 6, WHITE);
}
