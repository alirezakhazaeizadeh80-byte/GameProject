#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <stdio.h>
    float width;
    float height;
    int m,n;
    int playersCount;
    int huntersCount;
    int WallCount;
    int lightCoreH;
    int lightCoreW;
    int showError = 0;
    float maxsize;
    float MaxSize;
    int TextPrinted = 0;
    int BoardQuake = 0;
    int BonusCount = 5;
    int option = -1;
    char TextState = 'I';
    float TextTimer = -1;
    float MoveTimer = 0;
    int isQuake = 0; 
    int PickedHunter = -1;
    int HunterX = -1;
    int HunterY = -1;
    
    float fontsize = 10.0f;
    float FontSize = 10.0f;
    float speed = 50.0f;
    float Speed = 60.0f;
    int GameStoppage = 0;
    float transparency = 0.0;
    int selected = -1;
    char s = 'I';
    float timer = -1;
    int player = -1;
    int sw = 0;
    int counter = 0;
#endif