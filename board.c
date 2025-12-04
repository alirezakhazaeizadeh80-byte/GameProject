# include "board.h"

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width){
    for (int c = 1; c <= rows; c++)
        {
            DrawLine((c*cellWidth)+ 20, 20, (c*cellWidth) + 20, width -20, BLACK);
        }
    for (int r = 0; r < cols; r++)
        {
            DrawLine(20, (r*cellHeight) +20, 580.0, (r*cellHeight) +20, BLACK);
        }
        DrawRectangleLines(20, 20, width - 40, height - 40, BLACK);
}


void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight){
    Color lightcore = {90, 114, 104, 210};
    DrawRectangle((cellWidth * (rows-1)) + 20, (cellHeight * (cols-1)) +20, cellWidth, cellHeight, lightcore);
}

