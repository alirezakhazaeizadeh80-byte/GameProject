# include "board.h"
# include "bonus.h"
# include <math.h>
# include "inputs.h"
# include <time.h>

int min(int x1, int x2){
    if (x1 < x2) return x1;
    else return x2;
}
int max(int x1, int x2){
    if (x1 < x2) return x2;
    else return x1;
}


void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width){
    for (int c = 0; c <= cols; c++)
        {
            DrawLine((c*cellWidth)+ 20, 20, (c*cellWidth) + 20, height - 20, BLACK);
        }
    for (int r = 0; r <= rows; r++)
        {
            DrawLine(20, (r*cellHeight) +20, width - 20, (r*cellHeight) + 20, BLACK);
        }
        //DrawRectangleLines(20, 20, width - 40, height - 40, BLACK);
}


void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight){
    Color lightcore = {252, 250, 109, 250};
    DrawRectangle((cellWidth * (cols)) + 20, (cellHeight * (rows)) +20, cellWidth, cellHeight, lightcore);
}

void Showingpieces(Texture2D piece, int piecesNo, float pieces[][2], int cellWidth, int cellHeight, int playerMoved[], int state, float timer, float *transparency, char *s, int selected, int *PickedHunter, int *MovePlayerBonus){
    // state = 0 -> for players
    // state = 1 -> for huters
    float x, y, pX, pY; float scale, radius, centerX, centerY;
    if(*transparency >= 1.0)*s = 'D'; // Decrease transparency
    if(*transparency <= 0.3)*s = 'I'; // Increase transparency
    if(*s == 'I')*transparency += GetFrameTime()/3;
    else *transparency -= GetFrameTime()/3;
    for(int i = 0; i < piecesNo; i++){
        x = pieces[i][1] * cellWidth + 20;
        y = pieces[i][0] * cellHeight + 20;
        if(selected == i && state == 0){
            scale = 1.25 * (float)cellWidth / piece.width;
            pX = x + (cellWidth - scale * piece.width) / 2; // top corner
            pY = y + (cellHeight - scale * piece.height) / 2; // left corner
            DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
            continue;
        }
        scale = 1.1 * (float)cellWidth / piece.width;
        pX = x + (cellWidth - scale * piece.width) / 2; // top corner
        pY = y + (cellHeight - scale * piece.height) / 2; // left corner
        if(selected == i && state == 0){
            DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
            continue;
        }
        if(state == 0 && playerMoved[i] == 0){
            if(timer != -1 || *MovePlayerBonus != -1){
                if(timer>=0.6 || *MovePlayerBonus != -1)DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, Fade(WHITE, *transparency));
                else DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
            }
            else DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, Fade(WHITE, *transparency));
        }else{
            if(state == 0){
                scale = 1.1 * (float)cellWidth / piece.width;
            }
            if(state == 1 && *PickedHunter == i && !(IsKeyDown(KEY_T))){
                scale = 1.25 * (float)cellWidth / piece.width;
                //*PickedHunter = -1;
            }
            pX = x + (cellWidth - scale * piece.width) / 2;
            pY = y + (cellHeight - scale * piece.height) / 2;
            DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
        }
    }
}

void ShowingBonusBox(Texture2D box, int bonusCount, int bonuses[][2], int cellWidth, int cellHeight){
    int x, y, pX, pY; float scale;
    for(int i = 0; i < bonusCount; i++){
        x = bonuses[i][1] * cellWidth + 20;
        y = bonuses[i][0] * cellHeight + 20;
        scale = 1.05 * (float)cellWidth / box.width;
        pX = x + (cellWidth - scale * box.width)/2;
        pY = y + (cellHeight - scale * box.height)/2;
        DrawTextureEx(box, (Vector2){pX, pY}, 0, scale, WHITE);
    }
}


void tempWalls(int rows, int cols, int cellWidth, int cellHeight, Rectangle BlaWalls[][15][2]){
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            BlaWalls[j][i][1] = (Rectangle){(i*cellWidth) + 17, (j*cellHeight) + 20, 5, cellHeight};
            DrawRectangleRec(BlaWalls[j][i][1], BLANK);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            BlaWalls[i][j][0] = (Rectangle){(j*cellWidth) + 20, (i*cellHeight) + 17, cellWidth , 5};
            DrawRectangleRec(BlaWalls[i][j][0], BLANK);
        }
    }
}
int ShowingTempWalls(int rows, int cols, int walls[][2], int* wallCount ,char wallsState[], int* tempWallCounter, int isWall[][15][2], Vector2 mousePos, Rectangle BlaWalls[][15][2], int wallTurn[], int state, int BonusWalls[], int player){
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++){
            if (CheckCollisionPointRec(mousePos, BlaWalls[i][j][1])){
                walls[*wallCount][0] = i;
                walls[*wallCount][1] = j-1;
                wallsState[*wallCount] = 'V';
                isWall[i][j-1][1] = 1;
                wallTurn[*wallCount] = 3;
                *wallCount += 1;
                if(state == 0)*tempWallCounter -= 1;
                else{
                    BonusWalls[player] -= 1; if(BonusWalls[player] == 0)BonusWalls[player] = -1;
                }
                return 1;
                
                
            }
            if (CheckCollisionPointRec(mousePos, BlaWalls[i][j][0])){
                walls[*wallCount][0] = i-1;
                walls[*wallCount][1] = j;
                wallsState[*wallCount] = 'H';
                isWall[i-1][j][0] = 1;
                wallTurn[*wallCount] = 3;
                *wallCount += 1;
                if(state == 0)*tempWallCounter -= 1;
                else{
                    BonusWalls[player] -= 1; if(BonusWalls[player] == 0)BonusWalls[player] = -1;
                }
                return 1;
            }
            
            
            
            
        }
        
    }
    return 0;
    
}





void ShowingWalls(int wallCount ,int walls[][2], char wallsState[], int cellWidth, int cellHeight, int wallTurn[]){
    for (int i = 0; i < wallCount; i++)
    {
        if(wallTurn[i] == -1 || wallTurn[i] > 0){
            if (wallsState[i] == 'H')
            {
                int startXH = ((walls[i][1]) * cellWidth) + 20;
                int endXH = ((walls[i][1] + 1) * cellWidth) + 20;
                int startYH = ((walls[i][0] + 1) * cellHeight) + 20;
                int endYH = ((walls[i][0] + 1) * cellHeight) + 20;
                Vector2 startH = {startXH , startYH};
                Vector2 endH = {endXH , endYH};
                DrawLineEx(startH, endH, 5.0f, BLACK);
            }
            else if (wallsState[i] == 'V')
            {
                int startXV = ((walls[i][1] + 1) * cellWidth) + 20;
                int endXV = ((walls[i][1] + 1) * cellWidth) + 20;
                int startYV = ((walls[i][0]) * cellHeight) + 20;
                int endYV = ((walls[i][0] + 1) * cellHeight) + 20;
                Vector2 startV = {startXV , startYV};
                Vector2 endV = {endXV , endYV};
                DrawLineEx(startV, endV, 5.0f, BLACK);
            }
        }

            
        
    }
    
    
}

void showTempWall(Vector2 mousePos, int rows, int cols, int cellWidth, int cellHeight, int isWall[][15][2], Rectangle BlaWalls[][15][2]){
    int walls[2][2];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++){
            if (CheckCollisionPointRec(mousePos, BlaWalls[i][j][1])){
                walls[0][0] = i;
                walls[0][1] = j-1;
                char wallstate[1];
                wallstate[0] = 'V';
                int wallturn[200] = {-1};
                ShowingWalls(1,  walls, wallstate, cellWidth, cellHeight, wallturn);
                
            }
            if (CheckCollisionPointRec(mousePos, BlaWalls[i][j][0])){
                walls[0][0] = i-1;
                walls[0][1] = j;
                char wallstate[1];
                wallstate[0] = 'H';
                int wallturn[200] = {-1};
                ShowingWalls(1,  walls, wallstate, cellWidth, cellHeight, wallturn);
            }
        }
}
}
void SavingGame(int *lightCoreH, int *lightCoreW, int players[][2], int hunters[][2], int *playersCount, int *huntersCount, int walls[][2], int *n, int *m, int isWall[][15][2], int *BonusCount, int isBonus[][15], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][15], float oldHunters[][2], float oldPlayers[][2], char WallsState[], int *TempWallcounter, int *option, int WallTurn[], int *WallCount, int isHunter[][15], int *alivePlayers, int *counter){
    FILE *game = fopen("../game.dat", "wb");
    fwrite(n, sizeof(int), 1, game);
    fwrite(m, sizeof(int), 1, game);
    fwrite(lightCoreH, sizeof(int), 1, game);
    fwrite(lightCoreW, sizeof(int), 1, game);
    fwrite(playersCount, sizeof(int), 1, game);
    fwrite(huntersCount, sizeof(int), 1, game);
    fwrite(alivePlayers, sizeof(int), 1, game);
    fwrite(counter, sizeof(int), 1, game);
    fwrite(players, sizeof(int), (*alivePlayers) * 2, game);
    fwrite(hunters, sizeof(int), (*huntersCount) * 2, game);
    fwrite(walls, sizeof(int), 150 * 2, game);
    fwrite(isWall, sizeof(int), (*n) * (*m) * 2, game);
    fwrite(WallCount, sizeof(int),  1, game);
    fwrite(WallsState, sizeof(char), 150 * 2, game);
    fwrite(WallTurn, sizeof(int), 150 * 2, game);
    fwrite(isHunter, sizeof(int), (*n) * (*m), game);
    fwrite(PlHuDistance, sizeof(int), (*huntersCount) * (*alivePlayers), game);
    fwrite(TempWallcounter, sizeof(int), 1, game);
    fwrite(oldHunters, sizeof(int), (*huntersCount) * 2, game);
    fwrite(oldPlayers, sizeof(int), (*alivePlayers) * 2, game);
    fwrite(BonusCount, sizeof(int),  1, game);
    fwrite(isBonus, sizeof(int), (*n) * (*m), game);
    fwrite(bonuses, sizeof(int), (*BonusCount) * 2, game);
    fwrite(playerMoved, sizeof(int), (*alivePlayers), game);
    fwrite(BonusWalls, sizeof(int), (*alivePlayers), game);
    fwrite(option, sizeof(int), 1, game);
    fclose(game);
}

void ReturnGameBasics(FILE *game, int *lightCoreH, int *lightCoreW, int *playersCount, int *huntersCount, int isReturn, int *n, int *m, float *width, float *height, float *maxsize, float *MaxSize, float *cellHeight, float *cellWidth){
    if(isReturn == 1){
        fread(n, sizeof(int), 1, game);
        fread(m, sizeof(int), 1, game);
        fread(lightCoreH, sizeof(int), 1, game);
        fread(lightCoreW, sizeof(int), 1, game);
        fread(playersCount, sizeof(int), 1, game);
        fread(huntersCount, sizeof(int), 1, game);
    }
    else{
        printf("\n\033[32mWelcome to our game!\nthe minimum and maximum number of rows or columns is 5 and 12\nEnter the board dimensions : \033[0m");
        scanf("%d %d", n, m);
        while ((*n) < 5 || (*n) > 12 || (*m) < 5 || (*m) > 12)
        {
            printf("\033[31mThe input is invlalid!\033[0m\n");
            printf("\033[32mEnter the board dimensions : \033[0m");
            scanf("%d %d", n, m);
        }
        printf("\033[32mEnter the number of players : \033[0m");
        scanf("%d", playersCount);
        while((*playersCount) > 15 ){
            printf("\033[31mThe input is invlalid!\033[0m");
            printf("\033[32m\nEnter the number of players : \033[0m");
            scanf("%d", playersCount);
        }
        printf("\033[32mEnter the number of hunters : \033[0m");
        scanf("%d",huntersCount);
        while ((*huntersCount) > (*n)*(*m)/4)
        {
            printf("\033[31mThe input is invlalid!\033[0m\n");
            printf("\033[32mEnter the number of hunters : \033[0m");
            scanf("%d",huntersCount);
        }
        *lightCoreH = rand() % (*n);
        *lightCoreW = rand() % (*m);
    }
    if (abs((*n) - (*m)) < 4 )
    {
        *width = 700.0;
        *height= 700.0;
        *maxsize = 120.0f;
        *MaxSize = 35.0f;
    }
    else if ((*n) - (*m) >= 4)
    {
        *width = 400.0;
        *height = 700.0;
        *maxsize = 80.0f;
        *MaxSize = 20.0f;
    }
    else if ((*m) - (*n) >= 4)
    {
        *width = 800.0;
        *height = 500.0;
        *maxsize = 120.0f;
        *MaxSize= 35.0f;
    }
    *cellHeight = ((*height - 40) / (*n));
    *cellWidth = ((*width - 40) / (*m));
}

void ReturnGameDetails(FILE *game, int isReturn, int lightCoreH, int lightCoreW, int players[][2], int hunters[][2], int playersCount, int huntersCount, int walls[][2], int n, int m, int isWall[][15][2], int *BonusCount, int isBonus[][15], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][15], float oldHunters[][2], float oldPlayers[][2], char WallsState[], int *TempWallcounter, int *option, int WallTurn[], int *WallCount, int isHunter[][15], int *alivePlayers, int *counter, int dir[]){
    if(isReturn == 1){
        fread(alivePlayers, sizeof(int), 1, game);
        fread(counter, sizeof(int), 1, game);
        fread(players, sizeof(int), (*alivePlayers) * 2, game);
        fread(hunters, sizeof(int), huntersCount * 2, game);
        fread(walls, sizeof(int), 150 * 2, game);
        fread(isWall, sizeof(int), n * m * 2, game);
        fread(WallCount, sizeof(int), 1, game);
        fread(WallsState, sizeof(char), 150 * 2, game);
        fread(WallTurn, sizeof(int), 150 * 2, game);
        fread(isHunter, sizeof(int), n * m, game);
        fread(PlHuDistance, sizeof(int), huntersCount * (*alivePlayers), game);
        fread(TempWallcounter, sizeof(int), 1, game);
        fread(oldHunters, sizeof(int), huntersCount * 2, game);
        fread(oldPlayers, sizeof(int), (*alivePlayers) * 2, game);
        fread(BonusCount, sizeof(int),  1, game);
        fread(isBonus, sizeof(int), n * m, game);
        fread(bonuses, sizeof(int), (*BonusCount) * 2, game);
        fread(playerMoved, sizeof(int), (*alivePlayers), game);
        fread(BonusWalls, sizeof(int), (*alivePlayers), game);
        fread(option, sizeof(int), 1, game);
    }else{
        printf("\033[32mEnter the number of walls (max = %d): \033[0m",n*m-n-m+1);
        scanf("%d",WallCount);
        while(ControllingWalls(*WallCount, n, m, walls, WallsState, isWall) == 0){
            printf("\033[32mEnter the number of walls (max = %d): \033[0m",n*m-n-m+1);
            scanf("%d",WallCount);
        }
        int mark[15][15];
        for(int i=0; i<n; i++){
            for (int j=0; j<m; j++) mark[i][j] = 0;
        }
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
        for (int i = 0; i < huntersCount; i++)
        {
            for (int j = 0; j < playersCount; j++)
            {
                PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
            }
        }
        *TempWallcounter = max(min(n, m) / 3, 1);
        for(int i=0; i<huntersCount; i++){
            oldHunters[i][0]=(float)hunters[i][0];
            oldHunters[i][1]=(float)hunters[i][1];
        }
        for(int i=0; i<playersCount; i++){
            oldPlayers[i][0]=(float)players[i][0];
            oldPlayers[i][1]=(float)players[i][1];
        }
        (*alivePlayers) = playersCount;
        for(int i = 0; i < playersCount; i++)BonusWalls[i] = -1;
        for(int i=0; i<playersCount; i++)playerMoved[i] = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)isBonus[i][j] = 0;
        }
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
        for(int i = 0; i < (*WallCount); i++)WallTurn[i] = -1;
    }
    for(int i=0; i<huntersCount; i++)dir[i]=-1;
}

void LoadPiecesAndFonts(Texture2D *pieceRed, Texture2D *pieceBlue, Texture2D *box, Font *f, float maxsize){
    *pieceRed = LoadTexture("../pieces/redPieces.png");
    SetTextureFilter((*pieceRed), TEXTURE_FILTER_TRILINEAR);
    *pieceBlue = LoadTexture("../pieces/bluePieces.png");
    SetTextureFilter((*pieceBlue), TEXTURE_FILTER_TRILINEAR);
    *box = LoadTexture("../Bonus/BonusBox.png");
    SetTextureFilter((*box), TEXTURE_FILTER_TRILINEAR);
    *f = LoadFontEx("../fonts/LuckiestGuy-Regular.ttf", maxsize, 0, 0);
    SetTextureFilter((*f).texture, TEXTURE_FILTER_TRILINEAR);
}
