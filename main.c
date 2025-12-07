# include <stdio.h>
# include "raylib.h"
# include "raymath.h" 
# include "board.h"
int main() {
    float width;
    float height;
    int m,n;
    int ligthCoreH,lightcoreW;
    int playersCount;
    int shadowWhatcherCount;
    int WallCount;
    scanf("%d %d", &n, &m);
        if (abs(n - m) <= 4 )
    {
        width = 800.0;
        height= 800.0;
    }
    else if (n - m > 4)
    {
        width = 500.0;
        height = 800.0;
    }
    else if (m - n > 4)
    {
        width = 800.0;
        height = 500.0;
    }

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
    
    InitWindow(width, height, "The legend of the Labyrinth");
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

