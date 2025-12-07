# include <stdio.h>
# include "raylib.h"
# include "raymath.h" 
# include "board.h"
int main() {
    const int width = 600;
    const int height = 600;
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
    char WallsState[WallCount];
    int walls[WallCount][2];
    for (int i = 0; i < WallCount; i++)
    {
         scanf("%d %d %c",&walls[i][0], &walls[i][1], &WallsState[i]);
    }
    float cellHeight = ((height - 40) / n);
    float cellWidth = ((width - 40) / m);
    
    InitWindow(600, 600, "The legend of the Labyrinth");
    SetTargetFPS(60);
    Color Background = {213, 249, 222, 1};
    Texture2D pieceRed = LoadTexture("pieces/redPieces.png");
    SetTextureFilter(pieceRed, TEXTURE_FILTER_TRILINEAR);
    Texture2D pieceBlue = LoadTexture("pieces/bluePieces.png");
    SetTextureFilter(pieceBlue, TEXTURE_FILTER_TRILINEAR);

    while (!WindowShouldClose())
    {
        ClearBackground(Background);

        BeginDrawing();

        DrawGridB(n, m, cellWidth, cellHeight, height, width);
        ShowingLightcore(ligthCoreH, lightcoreW, cellWidth, cellHeight);
        Showingpieces(pieceRed, playersCount, players, cellWidth, cellHeight);
        Showingpieces(pieceBlue, shadowWhatcherCount, shadowWhatchers, cellWidth, cellHeight);
        ShowingWalls(WallCount ,walls, WallsState, cellWidth, cellHeight);

        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

