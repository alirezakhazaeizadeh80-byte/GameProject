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
    int sign[n][m][2];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            sign[i][j][0]=0;
            sign[i][j][1]=0;
        }
    }int isWall[n][m][2];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            isWall[i][j][0]=0;
            isWall[i][j][1]=0;
        }
    }
    for (int i = 0; i < WallCount; i++)
    {
        if (rand() % 2 == 0)
        {
            WallsState[i] = 'H';
            int X = rand() % (n-1);
            int Y = rand() % m;
            int sw=0;
            sign[X][Y][0]=1;
            dfs(X, Y, &sw, n, m, sign, 0, isWall);
            while(sw==2 || isWall[X][Y][0]==1){
            X = rand() % (n-1);
            Y = rand() % m;
            sw=0;
            sign[X][Y][0]=1;
            dfs(X, Y, &sw, n, m, sign, 0, isWall);
            }
            isWall[X][Y][0]=1;
            walls[i][0] = X;
            walls[i][1] = Y;
        }
        else
        {
            WallsState[i] = 'V';
            int X = rand() % n;
            int Y = rand() % (m-1);
            int sw=0;
            sign[X][Y][1]=1;
            dfs(X, Y, &sw, n, m, sign, 1, isWall);
            while(sw==2 || isWall[X][Y][1]==1){
            X = rand() % n;
            Y = rand() % (m-1);
            sw=0;
            sign[X][Y][1]=1;
            dfs(X, Y, &sw, n, m, sign, 1, isWall);
            }
            isWall[X][Y][1]=1;
            walls[i][0] = X;
            walls[i][1] = Y;
        }
        
    }
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

