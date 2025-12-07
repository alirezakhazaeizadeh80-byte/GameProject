# include <stdio.h>
# include "raylib.h"
# include "raymath.h" 
# include "board.h"
# include <time.h>
# include <stdlib.h>
# include "inputs.h"
# include <math.h>


int main() {
    float width;
    float height;
    srand(time(NULL));
    int m,n;
    int playersCount;
    int shadowWhatcherCount;
    int WallCount;
    int ligthCoreH;
    int lightCoreW;

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
    scanf("%d", &playersCount);
    int players[playersCount][2];
    scanf("%d",&shadowWhatcherCount);
    int shadowWhatchers[shadowWhatcherCount][2];
    scanf("%d",&WallCount);
    char WallsState[WallCount];
    int walls[WallCount][2];
    float cellHeight = ((height - 40) / n);
    float cellWidth = ((width - 40) / m);
    int mark[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)mark[i][j]=0;
    }

    ligthCoreH = rand() % n;
    lightCoreW = rand() % m;
    signing(ligthCoreH, lightCoreW, n, m, mark);

    for (int i = 0; i < playersCount; i++)
    {
        int X = rand() % n;
        int Y = rand() % m;
        while(mark[X][Y]){
        X = rand() % n;
        Y = rand() % m;
        }
        signing(X, Y, n, m, mark);
        players[i][0] = X;
        players[i][1] = Y;
    }

    for (int i = 0; i < shadowWhatcherCount; i++)
    {
        int X = rand() % n;
        int Y = rand() % m;
        while(mark[X][Y]){
            X = rand() % n;
            Y = rand() % m;
        }
        signing(X, Y, n, m, mark);
        shadowWhatchers[i][0] = X;
        shadowWhatchers[i][1] = Y;
        }
    ControllingWalls(WallCount, n, m, walls, WallsState);
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
        ShowingWalls(WallCount ,walls, WallsState, cellWidth, cellHeight);

        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

