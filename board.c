# include "board.h"

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

void Showingpieces(Texture2D piece, int piecesNo, float pieces[][2], int cellWidth, int cellHeight, int playerMoved[], int state, float timer, float *transparency, char *s, int selected, int *PickedHunter){
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
            if(timer != -1){
                if(timer>=0.6)DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, Fade(WHITE, *transparency));
                else DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
            }
            else DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, Fade(WHITE, *transparency));
        }else{
            if(state == 0){
                scale = 1.1 * (float)cellWidth / piece.width;
            }
            if(state == 1 && *PickedHunter == i){
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


void tempWalls(int rows, int cols, int cellWidth, int cellHeight, Rectangle BlaWalls[rows][cols][2]){
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
int ShowingTempWalls(int rows, int cols, int walls[][2], int* wallCount ,char wallsState[], int* tempWallCounter, int isWall[rows][cols][2], Vector2 mousePos, Rectangle BlaWalls[rows][cols][2], int wallTurn[], int state, int BonusWalls[], int player){
    
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

void showTempWall(Vector2 mousePos, int rows, int cols, int cellWidth, int cellHeight, int isWall[rows][cols][2], Rectangle BlaWalls[rows][cols][2]){
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
void SavingGame(int LightcoreH, int LightcoreW, int players[][2], int playersCount, int hunters[][2], int huntersCount, int isReturn, int walls[][2], int n, int m, int isWall[][m][2], int bonusCount, int isBonus[][m][2], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][playersCount], int oldHunters[][2], int oldPlayers[][2], char WallsState[], Rectangle BlaWalls[][m][2], int TempWallCount, int option, int WallTurn[]){
    FILE *game = fopen("C:\\desktop\\gameproject\\game.dat", "wb");
    fwrite(&isReturn, sizeof(int), 1, game);
    fwrite(&n, sizeof(int), 1, game);
    fwrite(&m, sizeof(int), 1, game);
    fwrite(&LightcoreH, sizeof(int), 1, game);
    fwrite(&LightcoreW, sizeof(int), 1, game);
    fwrite(&playersCount, sizeof(int), 1, game);
    fwrite(players, sizeof(int), playersCount * 2, game);
    fwrite(&huntersCount, sizeof(int), 1, game);
    fwrite(hunters, sizeof(int), huntersCount * 2, game);
    fwrite(isWall, sizeof(int), n * m * 2, game);
    fwrite(&bonusCount, sizeof(int),  1, game);
    fwrite(isBonus, sizeof(int), n * m * 2, game);
    fwrite(bonuses, sizeof(int), bonusCount, game);
    fwrite(playerMoved, sizeof(int), playersCount, game);
    fwrite(BonusWalls, sizeof(int), playersCount, game);
    fwrite(PlHuDistance, sizeof(int), huntersCount * playersCount, game);
    fwrite(oldHunters, sizeof(int), huntersCount * 2, game);
    fwrite(oldPlayers, sizeof(int), playersCount * 2, game);
    fwrite(WallsState, sizeof(char), 300 * 2, game);
    fwrite(WallTurn, sizeof(int), 300 * 2, game);
    fwrite(BlaWalls, sizeof(Rectangle), n * m * 2, game);
    fwrite(&TempWallCount, sizeof(int), 1, game);
    fwrite(&option, sizeof(int), 1, game);
}

void ReturnGame(int LightcoreH, int LightcoreW, int players[][2], int playersCount, int hunters[][2], int huntersCount, int isReturn, int walls[][2], int n, int m, int isWall[][m][2], int bonusCount, int isBonus[][m][2], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][playersCount], int oldHunters[][2], int oldPlayers[][2], char WallsState[300], Rectangle BlaWalls[][m][2], int TempWallCount, int option, int WallTurn[]){
    FILE *game = fopen("C:\\desktop\\gameproject\\game.dat", "rb");
    fread(&isReturn, sizeof(int), 1, game);
    if(isReturn == 0)return;
    fread(&n, sizeof(int), 1, game);
    fread(&m, sizeof(int), 1, game);
    fread(&LightcoreH, sizeof(int), 1, game);
    fread(&LightcoreW, sizeof(int), 1, game);
    fread(&playersCount, sizeof(int), 1, game);
    fread(players, sizeof(int), playersCount * 2, game);
    fread(&huntersCount, sizeof(int), 1, game);
    fread(hunters, sizeof(int), huntersCount * 2, game);
    fread(isWall, sizeof(int), n * m * 2, game);
    fread(&bonusCount, sizeof(int),  1, game);
    fread(isBonus, sizeof(int), n * m * 2, game);
    fread(bonuses, sizeof(int), bonusCount, game);
    fread(playerMoved, sizeof(int), playersCount, game);
    fread(BonusWalls, sizeof(int), playersCount, game);
    fread(PlHuDistance, sizeof(int), huntersCount * playersCount, game);
    fread(oldHunters, sizeof(int), huntersCount * 2, game);
    fread(oldPlayers, sizeof(int), playersCount * 2, game);
    fread(WallsState, sizeof(char), 300 * 2, game);
    fread(WallTurn, sizeof(int), 300 * 2, game);
    fread(BlaWalls, sizeof(Rectangle), n * m * 2, game);
    fread(&TempWallCount, sizeof(int), 1, game);
    fread(&option, sizeof(int), 1, game);
}
