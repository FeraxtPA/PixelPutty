#pragma once
#include "raylib.h"
#include "colors.h"
#include <string>

class UI
{
public:
	UI(int screenWidth, int screenHeight);
	~UI();
	void Draw();
	void SetStrokes(int strokes) { m_Strokes = strokes; }
	int GetTextWidth(std::string& string, int fontSize);
	int GetTextHeight(int fontSize);
	void DrawTextOutlined(const std::string& text, float posX, float posY, int fontSize, Color textColor, Color outlineColor, int outlineThickness, Font font);
	void LoadCustomFont(const std::string& filePath);
	

private:
	int m_Strokes{};
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	Font m_Font{};

};