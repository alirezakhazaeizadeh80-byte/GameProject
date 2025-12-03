#include "raylib.h"
#include "raymath.h" 

int main() {
    const int m,n;
    int ligthCoreH,lightcoreW;
    int playersCount;
    int shadowWhatcherCount;
    int WallCount;
    scanf("%d %d", &m, &n);
    scanf("%d %d",&ligthCoreH, &lightcoreW);
    scanf("%d", &playersCount);
    int players[playersCount][2];
    for (int i = 0; i < playersCount; i++)
    {
        scanf("%d %d", &players[i][0], &players[i][1]);
    }
    scanf("%d",&shadowWhatcherCount);
    int shadowWhatchers[shadowWhatcherCount][2];
    for (int i = 0; i < shadowWhatcherCount; i++)
    {
        scnaf("%d", &shadowWhatchers[i][0], &shadowWhatchers[i][1]);
    }
    scanf("%d",&WallCount);
    int walls[2][WallCount];
    for (int i = 0; i < WallCount; i++)
    {
        scanf("%d %d",&walls[i][0], &walls[i][1]);
    }
    
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

