#include "raylib.h"
#include "raymath.h" 

int main() {
    Color red = {255,0,0,255};
    InitWindow(600, 600, "Piece Move Animation");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(red);

        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

