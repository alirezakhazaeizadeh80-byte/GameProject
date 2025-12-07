# include "board.h"

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width){
    for (int c = 0; c <= cols; c++)
        {
            DrawLine((c*cellWidth)+ 20, 20, (c*cellWidth) + 20, height -20, BLACK);
        }
    for (int r = 0; r <= rows; r++)
        {
            DrawLine(20, (r*cellHeight) +20, width - 20, (r*cellHeight) +20, BLACK);
        }
}


void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight){
    Color lightcore = {252, 250, 109, 250};
    DrawRectangle((cellWidth * (cols)) + 20, (cellHeight * (rows)) +20, cellWidth, cellHeight, lightcore);
}

void Showingpieces(Texture2D piece, int piecesNo, int pieces[][2], int cellWidth, int cellHeight){
    int x, y, pX, pY; float scale;
    for(int i = 0; i < piecesNo; i++){
        x = pieces[i][1] * cellWidth + 20;
        y = pieces[i][0] * cellHeight + 20;
        scale = 1.1 * (float)cellWidth / piece.width;
        pX = x + (cellWidth - scale * piece.width) / 2;
        pY = y + (cellHeight - scale * piece.height) / 2;
        DrawTextureEx(piece, (Vector2){pX,pY}, 0, scale, WHITE);
    }
}

void ShowingWalls(int wallCount ,int walls[][2], char wallsState[], int cellWidth, int cellHeight){
    for (int i = 0; i < wallCount; i++)
    {
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


