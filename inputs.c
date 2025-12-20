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
int ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[], int isWall[][m][2]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            isWall[i][j][0] = 0;
            isWall[i][j][1] = 0;
        }
    }
    for (int i = 0; i < WallCount; i++)
    {
        int sign[n][m];
        time_t start = time(NULL);
        int sw=1;
        while(sw){            
            int state=rand() % 2; // Horizontal or vertical
            int X, Y;
            if(state == 0){
            X = rand() % (n-1);
            Y = rand() % m;
            }else{
                X = rand() % n;
                Y = rand() % (m-1);
            }
            if(isWall[X][Y][state] == 0){
                int counter = 1;
                isWall[X][Y][state] = 1;
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < m; j++){
                        sign[i][j] = 0;
                        }
                    }
                sign[0][0] = 1;
                dfs(0, 0, n, m, sign, &counter, isWall);
                if(counter!=n*m)isWall[X][Y][state]=0;
                while(counter != n*m){

                    if (time(NULL) - start >= 4)
                    {
                        printf("\033[31mThe number of walls is too high, Enter fewer.\n\033[0m\n");
                        return 0;
                    }

                    state = rand() % 2;
                    if(state == 0){
                        X = rand() % (n-1);
                        Y = rand() % m;
                    }else{
                        X = rand() % n;
                        Y = rand() % (m-1);
                    }
                    if(isWall[X][Y][state] == 0){
                        counter = 1;
                        isWall[X][Y][state] = 1;
                        for(int i = 0; i < n; i++){
                            for(int j = 0; j < m; j++){
                                sign[i][j] = 0;
                            }
                        }
                        sign[0][0] = 1;
                        dfs(0, 0, n, m, sign, &counter, isWall);
                        if(counter!=n*m)isWall[X][Y][state]=0;
                        }
                    }
                    if(state == 0){
                        WallsState[i] = 'H';
                    }else{
                        WallsState[i] = 'V';
                    }
                    walls[i][0] = X;
                    walls[i][1] = Y;
                    sw=0;
                }
            }
        }
    }
