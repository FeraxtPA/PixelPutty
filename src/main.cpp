#include "raylib.h"
#include "ball.h"
#include "iostream"

int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 1000;

    const int testCommit = 1;
    std::cout << testCommit;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetMouseCursor(MOUSE_CURSOR_ARROW);
    //SetTargetFPS(60);             
    SetExitKey(KEY_NULL);

    Ball ball{ screenWidth,screenHeight };
    while (!WindowShouldClose())
    {

        ball.Update();
        BeginDrawing();

        ClearBackground(DARKGRAY);

        ball.Draw();
        DrawFPS(10, 10);
        EndDrawing();


    }


    CloseWindow();

    return 0;
}