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
# include "bonus.h"
# include "pathfinding.h"
# include "definitions.h"
 

int main() {
    srand(time(NULL));
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
        width = 700.0;
        height= 700.0;
        maxsize = 120.0f;
        MaxSize = 35.0f;
    }
    else if (n - m >= 4)
    {
        width = 400.0;
        height = 700.0;
        maxsize = 90.0f;
        MaxSize = 20.0f;
    }
    else if (m - n >= 4)
    {
        width = 800.0;
        height = 500.0;
        maxsize = 100.0f;
        MaxSize= 35.0f;
    }
    printf("\033[32mEnter the number of players : \033[0m");
    scanf("%d", &playersCount);
    while(playersCount > 8 ){
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
    char WallsState[300];
    int walls[300][2];
    int isBonus[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)isBonus[i][j] = 0;
    }
    int wallTurn[300];
    for (int i = 0; i < WallCount; i++)
    {
        wallTurn[i] = -1;
    }
    
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
    float oldHunters[huntersCount][2];
    for(int i=0; i<huntersCount; i++){
        oldHunters[i][0]=(float)hunters[i][0];
        oldHunters[i][1]=(float)hunters[i][1];
    }
    float oldPlayers[playersCount][2];
    for(int i=0; i<playersCount; i++){
        oldPlayers[i][0]=(float)players[i][0];
        oldPlayers[i][1]=(float)players[i][1];
    }

    InitWindow(width, height, "The Tale of the Labyrinth");
    SetTargetFPS(60);
    Color Background = {213, 249, 222, 1};
    Texture2D pieceRed = LoadTexture("../pieces/redPieces.png");
    SetTextureFilter(pieceRed, TEXTURE_FILTER_TRILINEAR);
    Texture2D pieceBlue = LoadTexture("../pieces/bluePieces.png");
    SetTextureFilter(pieceBlue, TEXTURE_FILTER_TRILINEAR);
    Texture2D box = LoadTexture("../Bonus/BonusBox.png");
    SetTextureFilter(box, TEXTURE_FILTER_TRILINEAR);
    Font f = LoadFontEx("../fonts/LuckiestGuy-Regular.ttf", maxsize, 0, 0);
    SetTextureFilter(f.texture, TEXTURE_FILTER_TRILINEAR);
    
    
   
    Camera2D cam = {0};
    cam.offset = (Vector2){0, 0};
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;

    
    float shakeTimeLeft = 0.0f;
    float shakeIntensity = 5.0f;
    
    Vector2 shakeOffset = {0, 0};
    
    int alivePlayers = playersCount;
    int BonusWalls[playersCount];
    for(int i = 0; i < playersCount; i++)BonusWalls[i] = -1;
    int playerMoved[playersCount];
    for(int i=0; i<playersCount; i++)playerMoved[i] = 0;
    int bonuses[5][2];
    for(int i = 0; i < 5; i++){
        int x = rand() % n;
        int y = rand() % m;
        while(isBonus[x][y] == 1 || isHunter[x][y] == 1 || CheckPlayers(players, playersCount, x, y) == 1){
            x = rand() % n;
            y = rand() % m;
        }
        bonuses[i][0] = x;
        bonuses[i][1] = y;
        isBonus[x][y] = 1;
    }
    Rectangle BlaWalls[n][m][2];
    //memset(isBonus,0,sizeof(isBonus));
    while (!WindowShouldClose())
    {
        Pair path[150];
        int pathcount = 0;
        for (int i = 0; i < huntersCount; i++)
        {
            for (int j = 0; j < alivePlayers; j++)
            {
                PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
            }
        }
        for (int i = 0; i < huntersCount; i++)
        {
            for (int j = 0; j < alivePlayers; j++)
            {
                PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
            }
        }

       
        ClearBackground(Background);
        
        BeginDrawing();
        BeginMode2D(cam);
        tempWalls(n, m, cellWidth, cellHeight, BlaWalls);
        
        if(GameStoppage == 0){
            
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int x = GetMouseX();
                int y = GetMouseY();
                int cellX = (x)/cellWidth;
                int cellY = (y)/cellHeight;
                for(int i=0; i<alivePlayers; i++){
                    if(players[i][1] == cellX && players[i][0] == cellY && playerMoved[i] == 0){
                        
                        player = i;
                        sw = 1;
                        break;
                    }
                }

                if(sw == 0) player = -1;
                sw = 0;
                
            }
            if (IsKeyDown(KEY_T))
            {
                if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                    Vector2 mousePos = GetMousePosition();
                    if(player != -1 && BonusWalls[player] > 0){
                        if(ShowingTempWalls (n, m, walls, &WallCount, WallsState, &TempWallcounter, isWall, mousePos, BlaWalls, wallTurn, 1, BonusWalls, player) == 1){
                            playerMoved[player] = 1;
                        }
                    }
                    if (TempWallcounter > 0 && player != -1 && playerMoved[player] == 0){
                        if(ShowingTempWalls (n, m, walls, &WallCount, WallsState, &TempWallcounter, isWall, mousePos, BlaWalls, wallTurn, 0, BonusWalls, player) == 1){
                            playerMoved[player] = 1;
                        }
                    }
                }
                Vector2 mousePos = GetMousePosition();

                showTempWall(mousePos,n,m,cellWidth,cellHeight,isWall, BlaWalls);
            }
            if(playerMoved[player] == 0){
                if (IsKeyPressed(KEY_W))
                {
                    movePieces(n, m, players, player, walls, WallsState, WallCount,'W' , &showError, isWall, alivePlayers);                    
                    if(player != -1 && showError == 0){playerMoved[player] = 1;}
                }
                else if (IsKeyPressed(KEY_A))
                {
                    movePieces(n, m, players, player, walls, WallsState, WallCount, 'A', &showError, isWall, alivePlayers);                    
                    if(player != -1 && showError == 0){playerMoved[player] = 1;}
                }
                else if (IsKeyPressed(KEY_S))
                {
                    movePieces(n, m, players, player, walls, WallsState ,  WallCount, 'S' , &showError, isWall, alivePlayers);                    
                    if(player != -1 && showError == 0){playerMoved[player] = 1;}

                }
                else if (IsKeyPressed(KEY_D))
                {
                    movePieces(n, m, players, player, walls, WallsState,  WallCount, 'D', &showError, isWall, alivePlayers);
                    if(player != -1 && showError == 0){playerMoved[player] = 1;}
                }
                else if(IsKeyPressed(KEY_SPACE)){
                    if(player != -1 && showError == 0){playerMoved[player] = 1;}
                }
            }
            if(player != -1 && playerMoved[player] == 1){
                counter++;
                player = -1;
            }
            if(counter == alivePlayers){
                if(timer == -1){
                    timer = 0;
                }
                counter = 0;
                for(int i=0; i<alivePlayers; i++)playerMoved[i] = 0;
            }
            if(timer != -1)timer += GetFrameTime();
            if(timer >= 0.4){
               
                for (int i = WallCount - 1; wallTurn[i] > 0; i--)
                {
                    wallTurn[i]--;
                    int state;
                    if (WallsState[i] == 'H') state = 0;
                    else if (WallsState[i] == 'V') state = 1;
                    if(wallTurn[i] == 0)isWall[walls[i][0]][walls[i][1]][state] = 0;
                }
                for (int i = 0; i < huntersCount; i++)
                {
                    for (int j = 0; j < alivePlayers; j++)
                    {
                        PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
                    }
                }
                updateHunters(n, m, playersCount, hunters, huntersCount, players, alivePlayers, PlHuDistance, walls, WallsState, WallCount, isWall, isHunter, path, &pathcount, isBonus);

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
            if(BoardQuake == 1){
                shakeOffset.x = GetRandomValue(-shakeIntensity, shakeIntensity);
                shakeOffset.y = GetRandomValue(-shakeIntensity, shakeIntensity);
            }
            cam.offset = shakeOffset;

        }


            DrawGridB(n, m, cellWidth, cellHeight, height, width);
            ShowingLightcore(lightCoreH, lightCoreW, cellWidth, cellHeight);
            
            AnimatePieces(oldPlayers, players, playersCount, 3.0);
            Showingpieces(pieceRed, alivePlayers, oldPlayers, cellWidth, cellHeight, playerMoved, 0, timer, &transparency, &s, player, &PickedHunter);
            
            AnimatePieces(oldHunters, hunters, huntersCount, 3.0);
            Showingpieces(pieceBlue, huntersCount, oldHunters, cellWidth, cellHeight, playerMoved, 1, timer, &transparency, &s, player, &PickedHunter);
            
            ShowingWalls(WallCount ,walls, WallsState, cellWidth, cellHeight, wallTurn);
            ShowingBonusBox(box, BonusCount, bonuses, cellWidth, cellHeight);
            

            EndMode2D();
            CheckBonus(&option, &FontSize, MaxSize, Speed, playerMoved, width, height, f, &TextState, &TextTimer, &TextPrinted, hunters, huntersCount, n, m, isWall, cellWidth, cellHeight, &showError, alivePlayers, players, isBonus, &BonusCount, BonusWalls, &MoveTimer, isHunter, &BoardQuake, bonuses, &counter, &isQuake, &PickedHunter, &HunterX, &HunterY, lightCoreH, lightCoreW);
            Win(height, width, lightCoreH, lightCoreW, players, playersCount, f, &fontsize, maxsize, speed, &GameStoppage);
            Lose(height, width, m, players, &alivePlayers, hunters, huntersCount, isHunter, &fontsize, maxsize, speed, f, &GameStoppage, lightCoreH, lightCoreW, oldPlayers, oldHunters);

        EndDrawing();
    }
    //SavingGame(lightCoreH, lightCoreW, players, playersCount, hunters, huntersCount, isReturn, walls, n, m, isWall, BonusCount, isBonus, bonuses, playerMoved, BonusWalls, PlHuDistance, oldHunters, oldPlayers, WallsState, BlaWalls, TempWallcounter, option, wallTurn);
    


    CloseWindow();
    return 0;

}

