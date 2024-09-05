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
	void LoadOutlineShader(const std::string& filePath);
	void LoadCustomFont(const std::string& filePath);
	

private:
	int m_Strokes{};
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	Font m_Font{};
	Shader m_OutlineShader{};
	RenderTexture2D m_TextTexture{};
	std::string m_StrokeText{};
	int m_FontSize{};
};