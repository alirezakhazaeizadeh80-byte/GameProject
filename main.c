# include <stdio.h>
# include "raylib.h"
# include "raymath.h" 
# include "board.h"
# include <time.h>
# include <stdlib.h>
# include "inputs.h"
# include <math.h>
# include "movements.h"
# include <time.h>


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
    int showError;

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

    int isShadowWatcher[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            isShadowWatcher[i][j] = 0;
        }
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
        isShadowWatcher[X][Y] = 1;
        shadowWhatchers[i][0] = X;
        shadowWhatchers[i][1] = Y;
    }
    int isWall[n][m][2];
    ControllingWalls(WallCount, n, m, walls, WallsState, isWall);
    InitWindow(width, height, "The legend of the Labyrinth");
    SetTargetFPS(60);
    Color Background = {213, 249, 222, 1};
    Texture2D pieceRed = LoadTexture("pieces/redPieces.png");
    SetTextureFilter(pieceRed, TEXTURE_FILTER_TRILINEAR);
    Texture2D pieceBlue = LoadTexture("pieces/bluePieces.png");
    SetTextureFilter(pieceBlue, TEXTURE_FILTER_TRILINEAR);
    Font f = LoadFontEx("fonts/LuckiestGuy-Regular.ttf", 100, 0, 0);
    SetTextureFilter(f.texture, TEXTURE_FILTER_TRILINEAR);


    Camera2D cam = {0};
    cam.offset = (Vector2){0, 0};
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;


    float shakeTimeLeft = 0.0f;
    float shakeIntensity = 5.0f;

    Vector2 shakeOffset = {0, 0};

        float fontsize = 10.0f;
        float maxsize = 180.0f;
        float speed = 15.0f;




    int c = 0;
    while (!WindowShouldClose())
    {

        ClearBackground(Background);

        BeginDrawing();


        if (IsKeyPressed(KEY_W))
        {
            movePieces(n, m, players, 0, walls, WallsState, WallCount,'W' , &showError, isWall);
            if(showError != 1) updateShadowWatchers(n, m, shadowWhatchers, shadowWhatcherCount, players, 0, walls, WallsState, WallCount, isWall, isShadowWatcher);

        }
        else if (IsKeyPressed(KEY_A))
        {
            movePieces(n, m, players, 0, walls, WallsState, WallCount, 'A', &showError, isWall);
            if(showError != 1) updateShadowWatchers(n, m, shadowWhatchers, shadowWhatcherCount, players, 0, walls, WallsState, WallCount, isWall, isShadowWatcher);

        }
        else if (IsKeyPressed(KEY_S))
        {
            movePieces(n, m, players, 0, walls,WallsState ,  WallCount, 'S' , &showError, isWall);
            if(showError != 1) updateShadowWatchers(n, m, shadowWhatchers, shadowWhatcherCount, players, 0, walls, WallsState, WallCount, isWall, isShadowWatcher);

        }
        else if (IsKeyPressed(KEY_D))
        {
            movePieces(n, m, players, 0, walls, WallsState,  WallCount, 'D', &showError, isWall);
            if(showError != 1) updateShadowWatchers(n, m, shadowWhatchers, shadowWhatcherCount, players, 0, walls, WallsState, WallCount, isWall, isShadowWatcher);
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            if(showError != 1) updateShadowWatchers(n, m, shadowWhatchers, shadowWhatcherCount, players, 0, walls, WallsState, WallCount, isWall, isShadowWatcher);
        }
        if (showError == 1) {
            shakeTimeLeft = 0.2f;
            showError = 0;
        }
        if (shakeTimeLeft > 0) {
            shakeTimeLeft -= GetFrameTime();

            shakeOffset.x = GetRandomValue(-shakeIntensity, shakeIntensity);
            shakeOffset.y = GetRandomValue(-shakeIntensity, shakeIntensity);
        }

        cam.offset = shakeOffset;
        


        BeginMode2D(cam);

        DrawGridB(n, m, cellWidth, cellHeight, height, width);
        ShowingLightcore(ligthCoreH, lightCoreW, cellWidth, cellHeight);
        Showingpieces(pieceRed, playersCount, players, cellWidth, cellHeight);
        Showingpieces(pieceBlue, shadowWhatcherCount, shadowWhatchers, cellWidth, cellHeight);
        ShowingWalls(WallCount ,walls, WallsState, cellWidth, cellHeight);

        EndMode2D();
        if (fontsize < maxsize)
            {
                fontsize += speed * GetFrameTime();
            }

        
        Win(height, width, ligthCoreH, lightCoreW, players, 1, f, fontsize);


        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

