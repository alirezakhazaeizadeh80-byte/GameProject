#include "movements.h"


int hitWalls(int rows, int cols, int players[][2],int player, int walls[][2], int wallcount, char wallsstates[] , char move){
    int px = players[player][0];
    int py = players[player][1];
    if (move == 'W')
    {    
        for (int i = 0; i < wallcount; i++)
        {
            if (wallsstates[i] == 'H'){
                if ( walls[i][0] == px - 1 && walls[i][1] == py)
                {
                    return 1;
                }
            }
            
        }
    }    
    else if (move == 'S')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'H'){
               if ( walls[i][0] == px && walls[i][1] == py)
                {
                    return 1;
                }
        }        
        }
    }
    else if (move == 'A')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'V'){
                if ( walls[i][0] == px && walls[i][1] == py - 1)
                {
                    return 1;
                }
            }
        }
    }
    else if (move == 'D')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'V'){
                if ( walls[i][0] == px && walls[i][1] == py)
                {
                    return 1;
                }
            }    
        }
    }


    
    
}



void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror){
    if (move == 'W' && (players[player][0] <= 0 || hitWalls(rows, cols, players, player, walls, wallcount, wallsstates, 'W') == 1))
    {
        *showerror = 1;
    }
    else if (move == 'W')
    {
        players[player][0] -= 1;
    }
    if (move == 'A' && (players[player][1] <= 0 || hitWalls(rows, cols, players, player, walls, wallcount, wallsstates , 'A') == 1))
    {
        *showerror = 1;
    }
    else if (move == 'A')
    {
        players[player][1] -= 1;
    }
    if (move == 'S' && (players[player][0] >= ( rows - 1) || hitWalls(rows, cols, players, player, walls, wallcount, wallsstates, 'S') == 1 ) )
    {
        *showerror = 1;
    }
    else if (move == 'S')
    {
        players[player][0] += 1;
    }
    if (move == 'D' && (players[player][1] >= (cols - 1) ||  hitWalls(rows, cols, players, player, walls, wallcount, wallsstates,'D') == 1))
    {
        *showerror = 1;
    }
    else if (move == 'D')
    {
        players[player][1] += 1;
    }



}








