#include <math.h>
#include <limits.h>
#define MAX_OPEN 150
#define MAX_CLOSED 150
typedef struct{
    int row;
    int col;
} Pair;

typedef struct{
    int f;
    Pair p;
} pPair;

typedef struct{
    int parent_i;
    int parent_j;
    int f, g, h;
} cell;

void erase(pPair* openlist, int opencount, int index)
{
    for (int i = index + 1; i < opencount; i++) {
        openlist[i - 1] = openlist[i];
    }
}



int isValid(int rows, int cols, int i, int j)
{
    if((i >= 0) && (i < rows) && (j >= 0)&& (j < cols)) return 1 ;
    else return 0;
}

int isUnBlocked(int rows, int cols, Pair ori, Pair dest,  int isWall[rows][cols][2]){
    if (ori.col == dest.col && (ori.row - dest.row) == 1){
        if(isWall[ori.row-1][ori.col][0] == 1) return 0;
        else return 1;
    }
    else if (ori.col == dest.col && (ori.row - dest.row) == -1){
        if(isWall[(ori.row)][ori.col][0] == 1) return 0;
        else return 1;
    }
    else if (ori.row == dest.row && (ori.col - dest.col) == 1)
    {
        if(isWall[ori.row][ori.col-1][1] == 1) return 0;
        else return 1;
    }
    else if (ori.row == dest.row && (ori.col - dest.col) == -1)
    {
        if(isWall[ori.row][(ori.col)][1] == 1) return 0;
        else return 1;
    }
}

int isDestination(int i, int j, Pair dest){
    if(dest.row == i && dest.col == j) return 1;
    else return 0;
}

int calculateH(int i, int j, Pair dest){
    int ans;
    ans = abs(i-(dest.row)) + abs(j-(dest.col));
    return ans;
}

void tracepath(int rows , int cols, cell cells[][cols], Pair dest, Pair* paths, int *pathcount){
    *pathcount = 0;

    int i =  dest.row;
    int j =  dest.col;

    while (!(cells[i][j].parent_i == i && cells[i][j].parent_j == j))
    {
        paths[*pathcount].row = i;
        paths[*pathcount].col = j;
        (*pathcount)++;
        int tempI =cells[i][j].parent_i;
        int tempJ = cells[i][j].parent_j;
        i = tempI;
        j = tempJ;
    }
    
}

void aStar(int rows, int cols, int isWall[rows][cols][2], Pair ori, Pair dest, Pair* path, int *pathcount){
    if(ori.row == dest.row && ori.col == dest.col) return;
    int opencount = 0;

    cell cells[rows][cols];
    int closedlist[rows][cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            closedlist[i][j] = 0;
            cells[i][j].f = INT_MAX;
            cells[i][j].g = INT_MAX;
            cells[i][j].h = INT_MAX;
            cells[i][j].parent_i = -1;
            cells[i][j].parent_j = -1;
        }
    }
    int i = ori.row;
    int j = ori.col;
    cells[i][j].f = 0;
    cells[i][j].g = 0;
    cells[i][j].h = 0;
    cells[i][j].parent_i = i;
    cells[i][j].parent_j = j;
    
    pPair openlist[MAX_OPEN];
    openlist[opencount].f = 0;
    openlist[opencount].p.row = i;
    openlist[opencount].p.col = j;
    opencount++;

    while(opencount){

        int minfNode = openlist[0].f;
        int minIndex = 0;

        for (int i = 0; i < opencount; i++)
        {
            if (openlist[i].f < minfNode){
                minIndex = i;
                minfNode = openlist[i].f;
            }
        }
        int i = openlist[minIndex].p.row;
        int j = openlist[minIndex].p.col;
        
        erase(openlist, opencount, minIndex);
        opencount--;
        closedlist[i][j] = 1;

        int gNew, hNew, fNew;

        if (isValid(rows, cols, i-1, j))
        {
            if(isDestination(i-1, j, dest)){
                cells[i-1][j].parent_i = i;
                cells[i-1][j].parent_j = j;
                tracepath(rows, cols, cells, dest, path, pathcount);
                return;
            }

            else if(closedlist[i-1][j] == 0 && isUnBlocked(rows, cols, (Pair){i,j}, (Pair){i-1,j}, isWall) == 1){
                gNew = cells[i][j].g + 1;
                hNew = calculateH(i-1, j, dest);
                fNew = gNew + hNew;

                openlist[opencount].f = fNew;
                openlist[opencount].p.row = i-1;
                openlist[opencount].p.col = j;
                opencount++;

                if (cells[i-1][j].f == INT_MAX || cells[i-1][j].f > fNew)
                {
                    cells[i-1][j].f = fNew;
                    cells[i-1][j].g = gNew;
                    cells[i-1][j].h = hNew;
                    cells[i-1][j].parent_i = i;
                    cells[i-1][j].parent_j = j;
                }
                

            }
        }
        if (isValid(rows, cols, i+1, j))
        {
            if(isDestination(i+1, j, dest)){
                cells[i+1][j].parent_i = i;
                cells[i+1][j].parent_j = j;
                tracepath(rows, cols, cells, dest, path, pathcount);
                return;
            }

            else if(closedlist[i+1][j] == 0 && isUnBlocked(rows, cols, (Pair){i,j}, (Pair){i+1,j}, isWall) == 1){
                gNew = cells[i][j].g + 1;
                hNew = calculateH(i+1, j, dest);
                fNew = gNew + hNew;

                openlist[opencount].f = fNew;
                openlist[opencount].p.row = i+1;
                openlist[opencount].p.col = j;
                opencount++;

                if (cells[i+1][j].f == INT_MAX || cells[i+1][j].f > fNew)
                {
                    cells[i+1][j].f = fNew;
                    cells[i+1][j].g = gNew;
                    cells[i+1][j].h = hNew;
                    cells[i+1][j].parent_i = i;
                    cells[i+1][j].parent_j = j;
                }
                

            }
        }
        if (isValid(rows, cols, i, j+1))
        {
            if(isDestination(i, j+1, dest)){
                cells[i][j+1].parent_i = i;
                cells[i][j+1].parent_j = j;
                tracepath(rows, cols, cells, dest, path, pathcount);
                return;
            }

            else if(closedlist[i][j+1] == 0 && isUnBlocked(rows, cols, (Pair){i,j}, (Pair){i,j+1}, isWall) == 1){
                gNew = cells[i][j].g + 1;
                hNew = calculateH(i, j+1, dest);
                fNew = gNew + hNew;

                openlist[opencount].f = fNew;
                openlist[opencount].p.row = i;
                openlist[opencount].p.col = j+1;
                opencount++;

                if (cells[i][j+1].f == INT_MAX || cells[i][j+1].f > fNew)
                {
                    cells[i][j+1].f = fNew;
                    cells[i][j+1].g = gNew;
                    cells[i][j+1].h = hNew;
                    cells[i][j+1].parent_i = i;
                    cells[i][j+1].parent_j = j;
                }
                

            }
        }
        if (isValid(rows, cols, i, j-1))
        {
            if(isDestination(i, j-1, dest)){
                cells[i][j-1].parent_i = i;
                cells[i][j-1].parent_j = j;
                tracepath(rows, cols, cells, dest, path, pathcount);
                return;
            }

            else if(closedlist[i][j-1] == 0 && isUnBlocked(rows, cols, (Pair){i,j}, (Pair){i,j-1}, isWall) == 1){
                gNew = cells[i][j].g + 1;
                hNew = calculateH(i, j-1, dest);
                fNew = gNew + hNew;

                openlist[opencount].f = fNew;
                openlist[opencount].p.row = i;
                openlist[opencount].p.col = j-1;
                opencount++;

                if (cells[i][j-1].f == INT_MAX || cells[i][j-1].f > fNew)
                {
                    cells[i][j-1].f = fNew;
                    cells[i][j-1].g = gNew;
                    cells[i][j-1].h = hNew;
                    cells[i][j-1].parent_i = i;
                    cells[i][j-1].parent_j = j;
                }
                

            }
        }


        



    }



}



