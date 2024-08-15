#include "raylib.h"
#include "ball.h"

int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 1000;


    const int committest = 5;

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