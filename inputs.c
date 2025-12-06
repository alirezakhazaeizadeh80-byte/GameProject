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


