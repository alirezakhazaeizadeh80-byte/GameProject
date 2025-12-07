# include <stdio.h>

int controllingInputs(int players[][2],int playersCount, int shadowWatchers[][2],int shadowWatcherCont, int lightCoreH, int lightCoreW){
    for (int i = 0; i < playersCount; i++)
    {
        if ((players[i][0] - lightCoreW < 2) && (players[i][1] - lightCoreH < 2))
        {
            return 1;
        }
        
    }
    for (int i = 0; i < shadowWatcherCont; i++)
    {
        if ((shadowWatchers[i][0] - lightCoreW < 2) && (shadowWatchers[i][1] - lightCoreH < 2))
        {
            return 1;
        }
        
    }
    for (int i = 0; i < playersCount; i++)
    {
        for (int j = 0; j < shadowWatcherCont; j++)
        {
            if ((players[i][0] - shadowWatchers[j][0] < 2) && (shadowWatchers[i][1] - shadowWatchers[j][1] < 2))
        {
                return 1;
        }
        }
        
    }
    return 0;
    
    

}
void signing(int x, int y, int n, int m, int mark[][m]){
    mark[x][y]=1;
    if(x-1>=0)mark[x-1][y]=1;
    if(x+1<n)mark[x+1][y]=1;
    if(y-1>=0)mark[x][y-1]=1;
    if(y-1<m)mark[x][y+1]=1;
}
void dfs(int x, int y, int *sw, int n, int m, int sign[][m][2], int state, int isWall[][m][2]){
    if(state==0){
        if(y<m-1 && !sign[x][y][1] && isWall[x][y][1]){
            if(x==0)(*sw)++;
            sign[x][y][1]=1;
            dfs(x, y, sw, n, m, sign, 1, isWall);
        }
        if(y-1>=0 && !sign[x][y-1][1] && isWall[x][y-1][1]){
            if(x==0)(*sw)++;
            sign[x][y-1][1]=1;
            dfs(x, y-1, sw, n, m, sign, 1, isWall);
        }
        if((x+1<n && y<m-1) && !sign[x+1][y][1] && isWall[x+1][y][1]){
            if(x==n-2)(*sw)++;
            sign[x+1][y][1]=1;
            dfs(x+1, y, sw, n, m, sign, 1, isWall);
        }
        if((x+1<n && y-1>=0) && !sign[x+1][y-1][1] && isWall[x+1][y-1][1]){
            if(x==n-2)(*sw)++;
            sign[x+1][y-1][1]=1;
            dfs(x+1, y-1, sw, n, m, sign, 1, isWall);
        }
    }else if(state==1){
        if((x<m-1 && y+1<m) && !sign[x][y+1][0] && isWall[x][y+1][0]){
            if(y==m-2)(*sw)++;
            sign[x][y+1][0]=1;
            dfs(x, y+1, sw, n, m, sign, 0, isWall);
        }
        if((x-1>=0 && y+1<m) && !sign[x-1][y+1][0] && isWall[x-1][y+1][0]){
            if(y==m-2)(*sw)++;
            sign[x-1][y+1][0]=1;
            dfs(x-1, y+1, sw, n, m, sign, 0, isWall);
        }
        if(x-1>=0 && !sign[x-1][y][0] && isWall[x-1][y][0]){
            if(y==0)(*sw)++;
            sign[x-1][y][0]=1;
            dfs(x-1, y, sw, n, m, sign, 0, isWall);
        }
        if(x+1<=n-1 && !sign[x+1][y][0] && isWall[x+1][y][0]){
            if(y==0)(*sw)++;
            sign[x+1][y][0]=1;
            dfs(x+1, y, sw, n, m, sign, 0, isWall);
        }
    }
}

