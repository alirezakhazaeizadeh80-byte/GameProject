#include <stdio.h>
#include "raylib.h"
#include "raymath.h" 

int main() {
    int m,n;
    int ligthCoreH,lightcoreW;
    int playersCount;
    int shadowWhatcherCount;
    int WallCount;
    scanf("%d %d", &n, &m);
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
        scanf("%d %d", &shadowWhatchers[i][0], &shadowWhatchers[i][1]);
    }
    scanf("%d",&WallCount);
    int walls[2][WallCount];
    for (int i = 0; i < WallCount; i++)
    {
        scanf("%d %d",&walls[i][0], &walls[i][1]);
    }
    float cellHeight = (600.0-40.0) / n;
    float cellWidth = (600.0-40.0) / m;
    
    InitWindow(600, 600, "Piece Move Animation");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        for (int c = 0; c < m; c++)
        {
            DrawLine(c*cellWidth, 20, c*cellWidth, 580.0, BLACK);
        }
        for (int r = 0; r < n; r++)
        {
            DrawLine(20, r*cellHeight, 580.0, r*cellHeight, BLACK);
        }
        //DrawRectangleLines(20, 20, 560, 560, BLACK);
        //Texture2D peice_red=LoadTexture("red.png");
        //Texture2D peice_blue=LoadTexture("blue.png");
        ClearBackground(WHITE);
        
        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

