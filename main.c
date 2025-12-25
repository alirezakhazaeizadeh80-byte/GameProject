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
# include <stdbool.h>
# include <string.h>



int main() {
    float width;
    float height;
    srand(time(NULL));
    int m,n;
    int playersCount;
    int huntersCount;
    int WallCount;
    int lightCoreH;
    int lightCoreW;
    int showError;
    float maxsize;

    printf("\n\033[32mWelcome to our game!\nthe minimum and maximum number of rows or columns is 5 and 12\nEnter the board dimensions : \033[0m");
    scanf("%d %d", &n, &m);
    while (n < 5 || n > 12 || m < 5 || m > 12)
    {
        printf("\033[31mThe input is invlalid!\033[0m\n");
        printf("\033[32mEnter the board dimensions : \033[0m");
        scanf("%d %d", &n, &m);
    }
    
    if (abs(n - m) < 4 )
    {
        width = 800.0;
        height= 800.0;
        maxsize = 150.0f;
        
    }
    else if (n - m >= 4)
    {
        width = 500.0;
        height = 800.0;
        maxsize = 100.0f;
    }
    else if (m - n >= 4)
    {
        width = 800.0;
        height = 500.0;
        maxsize = 120.0f;

    }
    printf("\033[32mEnter the number of players : \033[0m");
    scanf("%d", &playersCount);
    while(playersCount > 4 ){
        printf("\033[31mThe input is invlalid!\033[0m");
        printf("\033[32m\nEnter the number of players : \033[0m");
        scanf("%d", &playersCount);
    }

    int players[playersCount][2];
    printf("\033[32mEnter the number of hunters : \033[0m");
    scanf("%d",&huntersCount);
    while (huntersCount > n*m/4)
    {
        printf("\033[31mThe input is invlalid!\033[0m\n");
        printf("\033[32mEnter the number of hunters : \033[0m");
        scanf("%d",&huntersCount);
    }
    
    int hunters[huntersCount][2];
    printf("\033[32mEnter the number of walls (max = %d): \033[0m",n*m-n-m+1);
    scanf("%d",&WallCount);
    char WallsState[n*m-n-m+1];
    int walls[n*m-n-m+1][2];
    // for (int i = 0; i < WallCount; i++)
    // {
    //     walls[i][2] = -1;
    // }
    
    int isWall[n][m][2];
    while(ControllingWalls(WallCount, n, m, walls, WallsState, isWall) == 0){
        printf("\033[32mEnter the number of walls (max = %d): \033[0m",n*m-n-m+1);
        scanf("%d",&WallCount);
    }
    float cellHeight = ((height - 40) / n);
    float cellWidth = ((width - 40) / m);
    int mark[n][m];
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++) mark[i][j] = 0;
    }

    lightCoreH = rand() % n;
    lightCoreW = rand() % m;
    signing(lightCoreH, lightCoreW, n, m, mark);

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

    int isHunter[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            isHunter[i][j] = 0;
        }
    }
    for (int i = 0; i < huntersCount; i++)
    {
        int X = rand() % n;
        int Y = rand() % m;
        while(mark[X][Y]){
            X = rand() % n;
            Y = rand() % m;
        }
        signing(X, Y, n, m, mark);
        isHunter[X][Y] = 1;
        hunters[i][0] = X;
        hunters[i][1] = Y;
    }
    int PlHuDistance[huntersCount][playersCount];
    for (int i = 0; i < huntersCount; i++)
    {
        for (int j = 0; j < playersCount; j++)
        {
            PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
        }
    }
    int TempWallcounter = max(min(n, m) / 3, 1);
    
    
    InitWindow(width, height, "The Tale of the Labyrinth");
    SetTargetFPS(60);
    Color Background = {213, 249, 222, 1};
    Texture2D pieceRed = LoadTexture("../pieces/redPieces.png");
    SetTextureFilter(pieceRed, TEXTURE_FILTER_TRILINEAR);
    Texture2D pieceBlue = LoadTexture("../pieces/bluePieces.png");
    SetTextureFilter(pieceBlue, TEXTURE_FILTER_TRILINEAR);
    Font f = LoadFontEx("../fonts/LuckiestGuy-Regular.ttf", maxsize, 0, 0);
    SetTextureFilter(f.texture, TEXTURE_FILTER_TRILINEAR);


    Camera2D cam = {0};
    cam.offset = (Vector2){0, 0};
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;


    float shakeTimeLeft = 0.0f;
    float shakeIntensity = 5.0f;

    Vector2 shakeOffset = {0, 0};

    float fontsize = 10.0f;
    float speed = 50.0f;
    int GameStoppage = 0;
    float timer = -1;
    int pressed = 0;
    int error;
    int player = -1;
    int sw = 0;
    int counter = 0;
    int playerMoved[playersCount];
    for(int i=0; i<playersCount; i++)playerMoved[i] = 0;



    Rectangle BlaWalls[n][m][2];
    while (!WindowShouldClose())
    {
        
        
        for (int i = 0; i < huntersCount; i++)
        {
            for (int j = 0; j < playersCount; j++)
            {
                PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
            }
        }
        
        
        
        
        ClearBackground(Background);
        
        BeginDrawing();
        tempWalls(n, m, cellWidth, cellHeight, BlaWalls);
        
        if(GameStoppage == 0){

            if (IsKeyDown(KEY_T))
            {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    Vector2 mousePos = GetMousePosition();
                if (TempWallcounter > 0){ 
                    if(ShowingTempWalls (n, m, walls, &WallCount, WallsState, &TempWallcounter, isWall, mousePos, BlaWalls) == 1){
                        updateHunters(n, m, hunters, huntersCount, players, playersCount, PlHuDistance, walls, WallsState, WallCount, isWall, isHunter);

                    }

                }
            }
                

                Vector2 mousePos = GetMousePosition();

                showTempWall(mousePos,n,m,cellWidth,cellHeight,isWall, BlaWalls);
            }
            
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                // Vector2 mousePos = GetMousePosition();
                // if (TempWallcounter > 0) ShowingTempWalls (n, m, walls, &WallCount, WallsState, &TempWallcounter, isWall, mousePos, BlaWalls);
                
                int x = GetMouseX();
                int y = GetMouseY();
                int cellX = (x)/cellWidth;
                int cellY = (y)/cellHeight;
                //printf("cell = (%d, %d)\n", cellX, cellY);
                for(int i=0; i<playersCount; i++){
                    if(players[i][1] == cellX && players[i][0] == cellY && playerMoved[i] == 0){
                        player = i;
                        sw = 1;
                        break;
                    }
                }

                if(sw == 0) player = -1;
                //else {printf("%d\n", playerMoved[player]); printf("%d\n", player);}
                sw = 0;
                
            }
            if (IsKeyDown(KEY_T))
            {
                //
            }
            
            if (IsKeyPressed(KEY_W))
            {
                movePieces(n, m, players, player, walls, WallsState, WallCount,'W' , &showError, isWall);
                if(player != -1){playerMoved[player] = 1;}
            }
            else if (IsKeyPressed(KEY_A))
            {
                movePieces(n, m, players, player, walls, WallsState, WallCount, 'A', &showError, isWall);
                if(player != -1){playerMoved[player] = 1;}
            }
            else if (IsKeyPressed(KEY_S))
            {
                movePieces(n, m, players, player, walls, WallsState ,  WallCount, 'S' , &showError, isWall);
                if(player != -1){playerMoved[player] = 1;}

            }
            else if (IsKeyPressed(KEY_D))
            {
                movePieces(n, m, players, player, walls, WallsState,  WallCount, 'D', &showError, isWall);
                if(player != -1){playerMoved[player] = 1;}
            }
            else if(IsKeyPressed(KEY_SPACE)){
                if(player != -1){playerMoved[player] = 1;}
            }
            if(player != -1 && playerMoved[player] == 1){
                counter++;
                player = -1;
            }
            if(counter == playersCount){
                if(timer == -1){
                    timer = 0;
                }
                //printf("%d\n", counter);
                counter = 0;
                for(int i=0; i<playersCount; i++)playerMoved[i] = 0;
            }
            if(timer != -1)timer += GetFrameTime();
            if(timer >= 0.4){
                updateHunters(n, m, hunters, huntersCount, players, playersCount, PlHuDistance, walls, WallsState, WallCount, isWall, isHunter);
                timer = -1;
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

        }
            BeginMode2D(cam);

            DrawGridB(n, m, cellWidth, cellHeight, height, width);
            ShowingLightcore(lightCoreH, lightCoreW, cellWidth, cellHeight);
            
            
            
            Showingpieces(pieceRed, playersCount, players, cellWidth, cellHeight);
            Showingpieces(pieceBlue, huntersCount, hunters, cellWidth, cellHeight);
            ShowingWalls(WallCount ,walls, WallsState, cellWidth, cellHeight);

            EndMode2D();
            Win(height, width, lightCoreH, lightCoreW, players, playersCount, f, &fontsize, maxsize, speed, &GameStoppage);
            Lose(height, width, m, players, playersCount, hunters, isHunter, &fontsize, maxsize, speed, f, &GameStoppage, lightCoreH, lightCoreW);
        

        EndDrawing();
    }
    
    


    CloseWindow();
    return 0;

}

