#include "background.h"
#include "TextureManager.h"

Background::Background(int width, int height)
{
    m_ScreenSize = { static_cast<float>(width), static_cast<float>(height) };
    m_BackgroundTexture = TextureManager::GetTexture(4, 0);
    m_TextureScale = 10;
}

Background::~Background()
{

    
}




void Background::Draw()
{
    /*
    int numCellsX = m_ScreenSize.x / m_CellSize;
    int numCellsY = m_ScreenSize.y / m_CellSize;

    for (int x = 0; x < numCellsX; ++x)
    {
        for (int y = 0; y < numCellsY; ++y)
        {
            if ((x + y) % 2 == 0)
            {
                DrawRectangle(x * m_CellSize, y * m_CellSize, m_CellSize, m_CellSize, m_Green);
            }
            else
            {
                DrawRectangle(x * m_CellSize, y * m_CellSize, m_CellSize, m_CellSize, m_DarkGreen);
            }
        }
    }*/

    //Scale the texture
    Rectangle sourceRec = { 0, 0, (float)m_ScreenSize.x / m_TextureScale, (float)m_ScreenSize.y / m_TextureScale };
    //Cover entire screen
    Rectangle destRec = { 0, 0, (float)m_ScreenSize.x, (float)m_ScreenSize.y };

    DrawTexturePro(m_BackgroundTexture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
}


