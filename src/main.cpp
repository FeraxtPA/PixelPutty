#include "raylib.h"
#include "game.h"

int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetMouseCursor(MOUSE_CURSOR_ARROW);
    //SetTargetFPS(60);             
    SetExitKey(KEY_NULL);

    Game game{ screenWidth, screenHeight };

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