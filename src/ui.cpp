#include "ui.h"

#include <iostream>

UI::UI(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	LoadCustomFont("assets/PixeloidMono.ttf");
}

UI::~UI()
{
	UnloadFont(m_Font);
}

void UI::Draw()
{

	float posX = m_ScreenWidth / 2.0f - 200.0f;
	float posY = -5.0f;
	float width = 400.0f;
	float height = 75.0f;
	Rectangle rect =
	{
		posX,
		posY,
		width,
		height
	};
	DrawRectangleRounded(rect, 0.2f, 4, PuttyColor::SetAlpha(PuttyColor::Black, 150));

	std::string strokeText = "Strokes:" + std::to_string(m_Strokes);

	int fontSize = 48;
	int textWidth = GetTextWidth(strokeText, fontSize);
	int textHeight = GetTextHeight(fontSize);

	
	float textPosX = posX + (width - textWidth) / 2.0f;
	float textPosY = posY + (height - textHeight) / 2.0f;

	
	DrawTextOutlined(strokeText, textPosX, textPosY, fontSize, PuttyColor::White, PuttyColor::Black, 4, m_Font);
}

int UI::GetTextWidth(std::string& string, int fontSize)
{
	return MeasureText(string.c_str(), fontSize);
}

int UI::GetTextHeight(int fontSize)
{
	return fontSize;
}

void UI::DrawTextOutlined(const std::string& text, float posX, float posY, int fontSize, Color textColor, Color outlineColor, int outlineThickness, Font font)
{

	// Top-left
	DrawTextEx(font, text.c_str(), { posX - outlineThickness, posY - outlineThickness }, fontSize, 1.0f, outlineColor);

	// Top
	DrawTextEx(font, text.c_str(), { posX, posY - outlineThickness }, fontSize, 1.0f, outlineColor);

	// Top-right
	DrawTextEx(font, text.c_str(), { posX + outlineThickness, posY - outlineThickness }, fontSize, 1.0f, outlineColor);

	// Left
	DrawTextEx(font, text.c_str(), { posX - outlineThickness, posY }, fontSize, 1.0f, outlineColor);

	// Right
	DrawTextEx(font, text.c_str(), { posX + outlineThickness, posY }, fontSize, 1.0f, outlineColor);

	// Bottom-left
	DrawTextEx(font, text.c_str(), { posX - outlineThickness, posY + outlineThickness }, fontSize, 1.0f, outlineColor);

	// Bottom
	DrawTextEx(font, text.c_str(), { posX, posY + outlineThickness }, fontSize, 1.0f, outlineColor);

	// Bottom-right
	DrawTextEx(font, text.c_str(), { posX + outlineThickness, posY + outlineThickness }, fontSize, 1.0f, outlineColor);

	// Draw the main text on top
	DrawTextEx(font, text.c_str(), { posX, posY }, fontSize, 1.0f, textColor);
}


void UI::LoadCustomFont(const std::string& filePath)
{
	m_Font = LoadFontEx(filePath.c_str(),84, NULL, 0);
}


