#include "ui.h"

#include <iostream>

UI::UI(int screenWidth, int screenHeight)
{
    m_FontSize = 64;
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	LoadCustomFont("assets/PixeloidMono.ttf");
	LoadOutlineShader("shaders/outline.fs");
	m_StrokeText = "Strokes: 0";
	Vector2 textSize = MeasureTextEx(m_Font, m_StrokeText.c_str(), m_FontSize, 2.0f);
	m_TextTexture = LoadRenderTexture((int)textSize.x + 40, (int)textSize.y + 40);  
}

UI::~UI()
{
	UnloadFont(m_Font);
	UnloadShader(m_OutlineShader);
	UnloadRenderTexture(m_TextTexture);
}

void UI::Draw()
{
    //Draw rectangle
    float posX = m_ScreenWidth / 2.0f - 200.0f;
    float posY = -5.0f;
    float width = 400.0f;
    float height = 75.0f;
    Rectangle rect = { posX, posY, width, height };
    DrawRectangleRounded(rect, 0.2f, 4, PuttyColor::SetAlpha(PuttyColor::Black, 150));


    // Update the stroke text
    m_StrokeText = "Strokes:" + std::to_string(m_Strokes);

    
    Vector2 textSize = MeasureTextEx(m_Font, m_StrokeText.c_str(), m_FontSize, 2.0f);

    // Resize the texture if needed
    if (m_TextTexture.texture.width < textSize.x + 40 || m_TextTexture.texture.height < textSize.y + 40)
    {
        UnloadRenderTexture(m_TextTexture);  
        m_TextTexture = LoadRenderTexture((int)textSize.x + 40, (int)textSize.y + 40);  
    }

    // Render the text to the texture
    BeginTextureMode(m_TextTexture);
    ClearBackground(BLANK);  // Ensure transparency
    DrawTextEx(m_Font, m_StrokeText.c_str(), {20,20}, m_FontSize, 2.0f, PuttyColor::White);
    EndTextureMode();


    // Set shader values for the outline shader
    Vector2 textureSize = { (float)m_TextTexture.texture.width, (float)m_TextTexture.texture.height };
    SetShaderValue(m_OutlineShader, GetShaderLocation(m_OutlineShader, "textureSize"), &textureSize, SHADER_UNIFORM_VEC2);


    Vector2 centeredPos = { posX + (width - (textSize.x + 40)) / 2, posY + (height - (textSize.y + 40)) / 2 };  
    // Apply the outline shader and draw the text texture inside the rectangle
    BeginShaderMode(m_OutlineShader);
    DrawTextureRec(m_TextTexture.texture, { 0, 0, (float)m_TextTexture.texture.width, (float)-m_TextTexture.texture.height }, centeredPos, WHITE);
    EndShaderMode();
}





void UI::LoadOutlineShader(const std::string& filePath)
{

	m_OutlineShader = LoadShader(NULL, filePath.c_str() );
	float outlineThickness = 4.0f;  
	Vector4 outlineColor = { 0.1019f, 0.1098f, 0.1725f, 1.0f }; // PuttyColor::Black equivalent
	SetShaderValue(m_OutlineShader, GetShaderLocation(m_OutlineShader, "outlineSize"), &outlineThickness, SHADER_UNIFORM_FLOAT);
	SetShaderValue(m_OutlineShader, GetShaderLocation(m_OutlineShader, "outlineColor"), &outlineColor, SHADER_UNIFORM_VEC4);
	
}

void UI::LoadCustomFont(const std::string& filePath)
{
	m_Font = LoadFontEx(filePath.c_str(),m_FontSize, NULL, 0);
}




