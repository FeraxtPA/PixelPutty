#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>

class TextureManager {
public:
    static void LoadSpriteSheet(const std::string& filePath, int tileWidth, int tileHeight);
    static void Unload();
    static Texture2D GetTexture(int tileIndexX, int tileIndexY);
    

private:
    static Texture2D m_SpriteSheet;
    static int m_TileWidth;
    static int m_TileHeight;
    static std::unordered_map<std::string, Texture2D> m_TextureMap;
};
