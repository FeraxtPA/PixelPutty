#include "raylib.h"
#include "game.h"
#include "TextureManager.h"


int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(screenWidth, screenHeight, "PixelPutty");
    SetMouseCursor(MOUSE_CURSOR_ARROW);
    //SetTargetFPS(165);             
    SetExitKey(KEY_NULL);

    TextureManager::LoadSpriteSheet("assets/Spritesheet.png", 8, 8);


    Game game{ screenWidth, screenHeight};

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        game.Update(deltaTime);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        game.Draw();
     
        DrawFPS(10, 10);
        EndDrawing();


    }


    CloseWindow();

    return 0;
}