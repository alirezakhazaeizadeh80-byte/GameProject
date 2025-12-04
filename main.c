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
    // scanf("%d",&WallCount);
    //int walls[WallCount][2];
    // for (int i = 0; i < WallCount; i++)
    // {
    //     scanf("%d %d",&walls[i][0], &walls[i][1]);
    // }
    float cellHeight = ((height - 40) / n);
    float cellWidth = ((width - 40) / m);
    
    InitWindow(600, 600, "The legend of the Labyrinth");
    SetTargetFPS(60);
    Color Background = {213, 249, 222, 1};
    Texture2D piece_red = LoadTexture("pieces/redPieces.png");
    SetTextureFilter(piece_red, TEXTURE_FILTER_TRILINEAR);
    Texture2D piece_blue = LoadTexture("pieces/bluePieces.png");
    SetTextureFilter(piece_blue, TEXTURE_FILTER_TRILINEAR);

    while (!WindowShouldClose())
    {
        ClearBackground(Background);

        BeginDrawing();

        DrawGridB(n, m, cellWidth, cellHeight, height, width);
        ShowingLightcore(ligthCoreH, lightcoreW, cellWidth, cellHeight);
        int x, y, pX, pY; float scale;
        for(int i=0; i<playersCount; i++){
            x = players[i][1] * cellWidth + 20;
            y = players[i][0] * cellHeight + 20;
            scale = 1.1 * (float)cellWidth / piece_blue.width;
            pX = x + (cellWidth - scale * piece_blue.width) / 2;
            pY = y + (cellHeight - scale * piece_blue.height) / 2;
            DrawTextureEx(piece_blue, (Vector2){pX,pY}, 0, scale, WHITE);
        }
        for(int i=0; i<shadowWhatcherCount; i++){
            x = shadowWhatchers[i][1] * cellWidth + 20;
            y = shadowWhatchers[i][0] * cellHeight + 20;
            scale = 1.1 * (float)cellWidth / piece_red.width;
            pX = x + (cellWidth - scale * piece_red.width) / 2;
            pY = y + (cellHeight - scale * piece_red.height) / 2;
            DrawTextureEx(piece_red, (Vector2){pX,pY}, 0, scale, WHITE);
        }
        EndDrawing();
    }
    


    CloseWindow();
    return 0;
}

