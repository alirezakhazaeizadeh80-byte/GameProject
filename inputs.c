# include <stdio.h>
# include <time.h>
# include <stdlib.h>

void signing(int x, int y, int n, int m, int mark[][m]){
    mark[x][y]=1;
    if(x-1>=0)mark[x-1][y]=1;
    if(x+1<n)mark[x+1][y]=1;
    if(y-1>=0)mark[x][y-1]=1;
    if(y+1<m)mark[x][y+1]=1;
    if(x-1>=0 && y-1>=0)mark[x-1][y-1]=1;
    if(x-1>=0 && y+1<m)mark[x-1][y+1]=1;
    if(x+1<n && y-1>=0)mark[x+1][y-1]=1;
    if(x+1<n && y+1<m)mark[x+1][y+1]=1;
}
void dfs(int x, int y, int n, int m, int sign[][m], int *counter, int isWall[][m][2]){
    if(x-1>=0 && !sign[x-1][y] && !isWall[x-1][y][0]){
        (*counter)++;
        sign[x-1][y] = 1;
        dfs(x-1, y, n, m, sign, counter, isWall);
        }
    if(x+1<n && !sign[x+1][y] && !isWall[x][y][0]){
        (*counter)++;
        sign[x+1][y] = 1;
        dfs(x+1, y, n, m, sign, counter, isWall);
        }
    if(y-1>=0 && !sign[x][y-1] && !isWall[x][y-1][1]){
        (*counter)++;
        sign[x][y-1] = 1;
        dfs(x, y-1, n, m, sign, counter, isWall);
        }
    if(y+1<m && !sign[x][y+1] && !isWall[x][y][1]){
        (*counter)++;
        sign[x][y+1] = 1;
        dfs(x, y+1, n, m, sign, counter, isWall);
        }
    }
void ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[]){
    int isWall[n][m][2];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            isWall[i][j][0] = 0;
            isWall[i][j][1] = 0;
        }
    }
    for (int i = 0; i < WallCount; i++)
    {
        int sign[n][m];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                sign[i][j] = 0;
            }
        }
        if (rand() % 2 == 0)
        {
            WallsState[i] = 'H';
            int X = rand() % (n-1);
            int Y = rand() % m;
            while(isWall[X][Y][0] == 1){
            X = rand() % (n-1);
            Y = rand() % m;
            }
            sign[0][0] = 1;
            int counter = 1;
            isWall[X][Y][0] = 1;
            dfs(0, 0, n, m, sign, &counter, isWall);
            while(counter != n*m){
            X = rand() % (n-1);
            Y = rand() % m;
            sign[0][0] = 1;
            counter = 1;
            isWall[X][Y][0] = 1;
            dfs(0, 0, n, m, sign, &counter, isWall);
            }
            walls[i][0] = X;
            walls[i][1] = Y;
        }
        else
        {
            WallsState[i] = 'V';
            int X = rand() % n;
            int Y = rand() % (m-1);
            while(isWall[X][Y][1] == 1){
            X = rand() % n;
            Y = rand() % (m-1);
            }
            sign[0][0] = 1;
            int counter = 1;
            isWall[X][Y][1] = 1;
            dfs(0, 0, n, m, sign, &counter, isWall);
            while(counter != n*m){
            X = rand() % n;
            Y = rand() % (m-1);
            sign[0][0] = 1;
            counter = 1;
            isWall[X][Y][1] = 1;
            dfs(0, 0, n, m, sign, &counter, isWall);
            }
            walls[i][0] = X;
            walls[i][1] = Y;
            
        }
        
    }
}

