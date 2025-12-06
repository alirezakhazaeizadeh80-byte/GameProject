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

