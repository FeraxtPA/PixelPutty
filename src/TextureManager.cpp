#include "TextureManager.h"

Texture2D TextureManager::m_SpriteSheet{};
int TextureManager::m_TileWidth = 0;
int TextureManager::m_TileHeight = 0;
std::unordered_map<std::string, Texture2D> TextureManager::m_TextureMap{};

void TextureManager::LoadSpriteSheet(const std::string& filePath, int tileWidth, int tileHeight)
{
    Unload();  // Ensure previous resources are unloaded
    m_SpriteSheet = LoadTexture(filePath.c_str());
    m_TileWidth = tileWidth;
    m_TileHeight = tileHeight;
}

void TextureManager::Unload()
{
    UnloadTexture(m_SpriteSheet);
    for (auto& texturePair : m_TextureMap)
    {
        UnloadTexture(texturePair.second);  
    }
    m_TextureMap.clear();  
}

Texture2D TextureManager::GetTexture(int tileIndexX, int tileIndexY)
{
    std::string key = std::to_string(tileIndexX) + "_" + std::to_string(tileIndexY);

    // Check if texture is already loaded
    auto it = m_TextureMap.find(key);
    if (it != m_TextureMap.end())
    {
        return it->second;
    }

    // Load the texture if not already cached
    int spriteWidth = m_TileWidth;
    int spriteHeight = m_TileHeight;

    Rectangle sourceRect = {
        static_cast<float>(tileIndexX) * spriteWidth,
        static_cast<float>(tileIndexY)  * spriteHeight,
        static_cast<float>(spriteWidth),
        static_cast<float>(spriteHeight)
    };

    Image spriteImage = LoadImageFromTexture(m_SpriteSheet);
    ImageCrop(&spriteImage, sourceRect);
    Texture2D spriteTexture = LoadTextureFromImage(spriteImage);
    UnloadImage(spriteImage);

    // Cache the texture
    m_TextureMap[key] = spriteTexture;

    return spriteTexture;
}
