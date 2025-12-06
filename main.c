# include <stdio.h>
# include "raylib.h"
# include "raymath.h" 
# include "board.h"
# include <time.h>
# include <stdlib.h>
# include "inputs.h"


int main() {
    const int width = 600;
    const int height = 600;
    srand(time(NULL));
    int m,n;
    int playersCount;
    int shadowWhatcherCount;
    int WallCount;
    int ligthCoreH;
    int lightCoreW;
    scanf("%d %d", &n, &m);
    scanf("%d", &playersCount);
    int players[playersCount][2];
    scanf("%d",&shadowWhatcherCount);
    int shadowWhatchers[shadowWhatcherCount][2];
    scanf("%d",&WallCount);
    char WallsState[WallCount];
    int walls[WallCount][2];
    float cellHeight = ((height - 40) / n);
    float cellWidth = ((width - 40) / m);
    do
    {   
        ligthCoreH = rand() % n;
        lightCoreW = rand() % m;
    
        for (int i = 0; i < playersCount; i++)
        {
            int X = rand() % n;
            int Y = rand() % m;
            players[i][0] = X;
            players[i][1] = Y;
        }

        for (int i = 0; i < shadowWhatcherCount; i++)
        {
            int X = rand() % n;
            int Y = rand() % m;
            shadowWhatchers[i][0] = X;
            shadowWhatchers[i][1] = Y;
        }
        for (int i = 0; i < WallCount; i++)
        {
            if (rand() % 2 == 0)
            {
                WallsState[i] = 'H';
            }
            else
            {
                WallsState[i] = 'V';
            }
            int X = rand() % n;
            int Y = rand() % m;
            walls[i][0] = X;
            walls[i][1] = Y;
        }
} while (controllingInputs(players, playersCount, shadowWhatchers, shadowWhatcherCount, ligthCoreH, lightCoreW) == 1);
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
        ShowingLightcore(ligthCoreH, lightCoreW, cellWidth, cellHeight);
        Showingpieces(pieceRed, playersCount, players, cellWidth, cellHeight);
        Showingpieces(pieceBlue, shadowWhatcherCount, shadowWhatchers, cellWidth, cellHeight);
        ShowingWalls(WallCount ,walls, WallsState, cellHeight, cellWidth);

        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

