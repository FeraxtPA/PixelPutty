#pragma once
#include "raylib.h"

class Background
{

public:


    Background(int width, int height);
    ~Background();
        
   
    void Draw();

private:
    Vector2 m_ScreenSize{};
    Texture2D m_BackgroundTexture;
    float m_TextureScale{1};

};