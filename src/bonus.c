#include "bonus.h"
#include "movements.h"
#include <stdio.h>
/*
 * File: bonus.c
 * Purpose: Bonus selection, effects, and supporting helpers.
 */

/* Allow the player to pick and move a hunter during the bonus. */
int PickHunter(int hunters[][2], int huntersCount, float cellWidth, float cellHeight, int n, int m, int isWall[][15][2], int *PickBonusCount, int isHunter[][15], int *TextPrinted, int *PickedHunter, int *HunterX, int *HunterY, int players[][2], int alivePlayers)
{
    int x;
    int y;
    int error = 0;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        x = GetMouseX();
        y = GetMouseY();
        *HunterX = (x) / cellWidth;
        *HunterY = (y) / cellHeight;
    }
    if (isHunter[*HunterY][*HunterX] == 0)
    {
        *PickedHunter = -1;
        return 0;
    }
    int ind = FindIndex(hunters, huntersCount, *HunterY, *HunterX);
    *PickedHunter = ind;
    if (IsKeyPressed(KEY_W))
    {
        if (hunters[ind][0] == 0 || isWall[hunters[ind][0] - 1][hunters[ind][1]][0] == 1 || isHunter[hunters[ind][0] - 1][hunters[ind][1]] == 1 || CheckPlayers(players, alivePlayers, hunters[ind][0] - 1, hunters[ind][1]) == 1)
            error = 1;
        else
        {
            hunters[ind][0] -= 1;
            (*PickBonusCount) -= 1;
            isHunter[*HunterY][*HunterX] = 0;
            isHunter[*HunterY - 1][*HunterX] = 1;
            *PickedHunter = -1;
        }
    }
    else if (IsKeyPressed(KEY_A))
    {
        if (hunters[ind][1] == 0 || isWall[hunters[ind][0]][hunters[ind][1] - 1][1] == 1 || isHunter[hunters[ind][0]][hunters[ind][1] - 1] == 1 || CheckPlayers(players, alivePlayers, hunters[ind][0], hunters[ind][1] - 1) == 1)
            error = 1;
        else
        {
            hunters[ind][1] -= 1;
            (*PickBonusCount) -= 1;
            isHunter[*HunterY][*HunterX] = 0;
            isHunter[*HunterY][*HunterX - 1] = 1;
            *PickedHunter = -1;
        }
    }
    else if (IsKeyPressed(KEY_S))
    {
        if (hunters[ind][0] == n - 1 || isWall[hunters[ind][0]][hunters[ind][1]][0] == 1 || isHunter[hunters[ind][0] + 1][hunters[ind][1]] == 1 || CheckPlayers(players, alivePlayers, hunters[ind][0] + 1, hunters[ind][1]) == 1)
            error = 1;
        else
        {
            hunters[ind][0] += 1;
            (*PickBonusCount) -= 1;
            isHunter[*HunterY][*HunterX] = 0;
            isHunter[*HunterY + 1][*HunterX] = 1;
            *PickedHunter = -1;
        }
    }
    else if (IsKeyPressed(KEY_D))
    {
        if (hunters[ind][1] == m - 1 || isWall[hunters[ind][0]][hunters[ind][1]][1] == 1 || isHunter[hunters[ind][0]][hunters[ind][1] + 1] == 1 || CheckPlayers(players, alivePlayers, hunters[ind][0], hunters[ind][1] + 1) == 1)
            error = 1;
        else
        {
            hunters[ind][1] += 1;
            (*PickBonusCount) -= 1;
            isHunter[*HunterY][*HunterX] = 0;
            isHunter[*HunterY][*HunterX + 1] = 1;
            *PickedHunter = -1;
        }
    }
    return error;
}
/* Find an index in a 2D list of positions. */
int FindIndex(int array[][2], int arrayCount, int x, int y)
{
    for (int i = 0; i < arrayCount; i++)
    {
        if (x == array[i][0] && y == array[i][1])
            return i;
    }
    return -1;
}
/* Check whether any player occupies the given grid cell. */
int CheckPlayers(int players[][2], int alivePlayers, int x, int y)
{
    for (int i = 0; i < alivePlayers; i++)
    {
        if (players[i][0] == x && players[i][1] == y)
            return 1;
    }
    return 0;
}
/* Randomly move players and hunters during the board quake bonus. */
void ChangePositionsRandomly(int players[][2], int hunters[][2], int aliveplayers, int huntersCount, int n, int m, int isHunter[][15], int isWall[][15][2], int isBonus[][15])
{
    srand(time(NULL));
    int dir;
    int moods = 4;
    int ignore[4];
    for (int i = 0; i < 4; i++)
        ignore[i] = 0;
    for (int i = 0; i < aliveplayers; i++)
    {
        if (moods == 0)
        { // means there is no valid neighbor cell for this player to move
            moods = 4;
            for (int j = 0; j < 4; j++)
                ignore[j] = 0;
            continue;
        }
        dir = rand() % 4;
        while (ignore[dir] == 1)
        { // means this direction is invalid (player can't move through this)
            dir = rand() % 4;
        }
        switch (dir)
        {
        case 0: // Go up
            if (players[i][0] > 0 && isWall[players[i][0] - 1][players[i][1]][0] == 0 && CheckPlayers(players, aliveplayers, (players[i][0] - 1), players[i][1]) == 0 && isBonus[players[i][0] - 1][players[i][1]] == 0)
            {
                players[i][0] -= 1;
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0; // for next player
                moods = 4;
            }
            else
            {
                ignore[0] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 1: // Go down
            if (players[i][0] < n - 1 && isWall[players[i][0]][players[i][1]][0] == 0 && CheckPlayers(players, aliveplayers, (players[i][0] + 1), players[i][1]) == 0 && isBonus[players[i][0] + 1][players[i][1]] == 0)
            {
                players[i][0] += 1;
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
            }
            else
            {
                ignore[1] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 2: // Go right
            if (players[i][1] < m - 1 && isWall[players[i][0]][players[i][1]][1] == 0 && CheckPlayers(players, aliveplayers, players[i][0], (players[i][1] + 1)) == 0 && isBonus[players[i][0]][players[i][1] + 1] == 0)
            {
                players[i][1] += 1;
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
            }
            else
            {
                ignore[2] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 3: // Go left
            if (players[i][1] > 0 && isWall[players[i][0]][players[i][1] - 1][1] == 0 && CheckPlayers(players, aliveplayers, players[i][0], (players[i][1] - 1)) == 0 && isBonus[players[i][0]][players[i][1] - 1] == 0)
            {
                players[i][1] -= 1;
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
            }
            else
            {
                ignore[3] = 1;
                moods -= 1;
                i--;
            }
            break;
        }
    }
    for (int i = 0; i < huntersCount; i++)
    {
        if (moods == 0)
        { // means there is no valid neighbor cell for this hunter to move
            moods = 4;
            for (int j = 0; j < 4; j++)
                ignore[j] = 0;
            continue;
        }
        dir = rand() % 4;
        while (ignore[dir] == 1)
        { // means this direction is invalid (hunter can't move through this)
            dir = rand() % 4;
        }
        switch (dir)
        {
        case 0: // Go up
            if (hunters[i][0] > 0 && isWall[hunters[i][0] - 1][hunters[i][1]][0] == 0 && isHunter[hunters[i][0] - 1][hunters[i][1]] == 0 && isBonus[hunters[i][0] - 1][hunters[i][1]] == 0)
            {
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0; // for next hunter
                moods = 4;
                isHunter[hunters[i][0]][hunters[i][1]] = 0;
                isHunter[hunters[i][0] - 1][hunters[i][1]] = 1;
                hunters[i][0] -= 1;
            }
            else
            {
                ignore[0] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 1: // Go down
            if (hunters[i][0] < n - 1 && isWall[hunters[i][0]][hunters[i][1]][0] == 0 && isHunter[hunters[i][0] + 1][hunters[i][1]] == 0 && isBonus[hunters[i][0] + 1][hunters[i][1]] == 0)
            {
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
                isHunter[hunters[i][0]][hunters[i][1]] = 0;
                isHunter[hunters[i][0] + 1][hunters[i][1]] = 1;
                hunters[i][0] += 1;
            }
            else
            {
                ignore[1] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 2: // Go right
            if (hunters[i][1] < m - 1 && isWall[hunters[i][0]][hunters[i][1]][1] == 0 && isHunter[hunters[i][0]][hunters[i][1] + 1] == 0 && isBonus[hunters[i][0]][hunters[i][1] + 1] == 0)
            {
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
                isHunter[hunters[i][0]][hunters[i][1]] = 0;
                isHunter[hunters[i][0]][hunters[i][1] + 1] = 1;
                hunters[i][1] += 1;
            }
            else
            {
                ignore[2] = 1;
                moods -= 1;
                i--;
            }
            break;
        case 3: // Go left
            if (hunters[i][1] > 0 && isWall[hunters[i][0]][hunters[i][1] - 1][1] == 0 && isHunter[hunters[i][0]][hunters[i][1] - 1] == 0 && isBonus[hunters[i][0]][hunters[i][1] - 1] == 0)
            {
                for (int j = 0; j < 4; j++)
                    ignore[j] = 0;
                moods = 4;
                isHunter[hunters[i][0]][hunters[i][1]] = 0;
                isHunter[hunters[i][0]][hunters[i][1] - 1] = 1;
                hunters[i][1] -= 1;
            }
            else
            {
                ignore[3] = 1;
                moods -= 1;
                i--;
            }
            break;
        }
    }
}
/* Draw a black outline around text to improve readability. */
void TextOutline(Vector2 pos, Vector2 origin, float fontSize, const char *str, Font f)
{
    for (int i = -4; i <= 4; i++)
    {
        for (int j = -4; j <= 4; j++)
        {
            if (i == 0 && j == 0)
                continue;
            Vector2 p = {pos.x + i, pos.y + j};
            DrawTextPro(f, str, p, origin, 0.0, fontSize, 2, BLACK);
        }
    }
}
/* Evaluate and apply bonus effects, including animations and input handling. */
void CheckBonus(int *option, float *fontsize, float maxsize, float speed, int playerMoved[], int width, int height, Font f, char *TextState, float *TextTimer, int *TextPrinted, int hunters[][2], int huntersCount, int n, int m, int isWall[][15][2], int cellWidth, int cellHeight, int *showError, int alivePlayers, int players[][2], int IsBonus[][15], int *BonusesCount, int BonuaWalls[], float *MoveTimer, int isHunter[][15], int *BoardQuake, int bonuses[][2], int *counter, int *isQuake, int *PickedHunter, int *HunterX, int *HunterY, int LightcoreX, int LightcoreY, float oldHunters[][2], int *PickBonusCount, int *MovePlayerBonus)
{
    int player = -1;
    if (*option == -1)
    {
        for (int i = 0; i < alivePlayers; i++)
        {
            if (IsBonus[players[i][0]][players[i][1]] == 1 && (players[i][0] != LightcoreX || players[i][1] != LightcoreY))
            {
                *option = rand() % 4;
                if (*option == 3)
                    (*PickBonusCount) += 1; // related to Pick_Hunter bonus
                player = i;
                for (int j = FindIndex(bonuses, *BonusesCount, players[i][0], players[i][1]); j < *BonusesCount - 1; j++)
                {
                    bonuses[j][0] = bonuses[j + 1][0];
                    bonuses[j][1] = bonuses[j + 1][1];
                }
                IsBonus[players[i][0]][players[i][1]] = 0;
                (*BonusesCount) -= 1;
            }
        }
    }
    for (int i = 0; i < huntersCount; i++)
    {
        if (IsBonus[hunters[i][0]][hunters[i][1]] == 1)
        {
            if (fabsf(oldHunters[i][0] - (float)hunters[i][0]) <= 0.02 && fabsf(oldHunters[i][1] - (float)hunters[i][1]) <= 0.02)
            {
                for (int j = FindIndex(bonuses, *BonusesCount, hunters[i][0], hunters[i][1]); j < *BonusesCount - 1; j++)
                {
                    bonuses[j][0] = bonuses[j + 1][0];
                    bonuses[j][1] = bonuses[j + 1][1];
                }
                IsBonus[hunters[i][0]][hunters[i][1]] = 0;
                (*BonusesCount) -= 1;
            }
        }
    }
    if (*PickBonusCount > 0)
    { // related to Pick_Hunter bonus
        if (PickHunter(hunters, huntersCount, cellWidth, cellHeight, n, m, isWall, PickBonusCount, isHunter, TextPrinted, PickedHunter, HunterX, HunterY, players, alivePlayers) == 1)
            *showError = 1;
    }
    if (*option == -1)
        return; // No bonus
    switch (*option)
    {
    case 0:
        if (*fontsize >= maxsize)
        {
            *TextState = 'D';
            if (*TextTimer == -1)
                *TextTimer = 0;
        }
        if (*TextState == 'I')
        {
            *fontsize += speed * GetFrameTime();
        }
        else if ((*TextTimer) >= 1.2)
        {
            *fontsize -= speed * GetFrameTime();
        }
        if (*TextTimer != -1)
            *TextTimer += GetFrameTime();
        char str1[50] = "You can move this player again!";
        Color color1 = {0, 194, 50, 255};
        Vector2 textSize1 = MeasureTextEx(f, str1, *fontsize, 2);
        Vector2 pos1 = {width / 2, height / 2};
        Vector2 origin1 = {textSize1.x / 2, textSize1.y / 2};
        TextOutline(pos1, origin1, *fontsize, str1, f);
        DrawTextPro(f, str1, pos1, origin1, 0.0f, *fontsize, 2, color1);
        if (*fontsize <= 0.0)
        {
            *option = -1;
            *TextTimer = -1;
            *TextState = 'I';
        }
        if (player != -1)
        {
            playerMoved[player] = 0;
            (*counter) -= 1;
            if ((*counter) == (alivePlayers - 1))
                *MovePlayerBonus = 1; // for debug unwanted game stopping
        }
        break;
    case 1:
        if (*fontsize >= maxsize)
        {
            *TextState = 'D';
            if (*TextTimer == -1)
                *TextTimer = 0;
        }
        if (*TextState == 'I')
        {
            *fontsize += speed * GetFrameTime();
        }
        else if ((*TextTimer) >= 2.3)
        {
            *fontsize -= speed * GetFrameTime();
        }
        if (*TextTimer != -1)
            (*TextTimer) += GetFrameTime();
        char str2[60] = "         This player can place\n more two temporary walls!";
        Color color2 = {11, 55, 191, 255};
        Vector2 textSize2 = MeasureTextEx(f, str2, *fontsize, 2);
        Vector2 pos2 = {width / 2, height / 2};
        Vector2 origin2 = {textSize2.x / 2, textSize2.y / 2};
        TextOutline(pos2, origin2, *fontsize, str2, f);
        DrawTextPro(f, str2, pos2, origin2, 0.0f, *fontsize, 2, color2);
        if (*fontsize <= 0.0)
        {
            *option = -1;
            *TextTimer = -1;
            *TextState = 'I';
        }
        if (player != -1)
        {
            if (BonuaWalls[player] == -1)
                BonuaWalls[player] = 2;
            else
                BonuaWalls[player] += 2;
        }
        break;
    case 2:
        if (*fontsize >= maxsize)
        {
            *TextState = 'D';
            if (*TextTimer == -1)
                *TextTimer = 0;
        }
        if (*TextState == 'I')
        {
            *fontsize += speed * GetFrameTime();
        }
        else if ((*TextTimer) >= 1.5)
        {
            *fontsize -= speed * GetFrameTime();
        }
        if (*TextTimer != -1)
            *TextTimer += GetFrameTime();
        char str3[50] = "Your bonus is Board Quake!";
        Color color3 = {0, 232, 189, 255};
        Vector2 textSize3 = MeasureTextEx(f, str3, *fontsize, 2);
        Vector2 pos3 = {width / 2, height / 2};
        Vector2 origin3 = {textSize3.x / 2, textSize3.y / 2};
        TextOutline(pos3, origin3, *fontsize, str3, f);
        DrawTextPro(f, str3, pos3, origin3, 0.0f, *fontsize, 2, color3);
        if (*fontsize <= 0.0)
        {
            *option = -1;
            *TextTimer = -1;
            *TextState = 'I';
        }
        if (*MoveTimer <= 1.8 && *option != -1)
        {
            *BoardQuake = 1;
            (*MoveTimer) += 1.0f * GetFrameTime();
        }
        else
        {
            *BoardQuake = 0;
            *MoveTimer = 0;
            *TextPrinted = 0;
            *isQuake = 0;
        }
        if (*MoveTimer >= 1.2 && *MoveTimer <= 1.8 && *isQuake == 0)
        {
            ChangePositionsRandomly(players, hunters, alivePlayers, huntersCount, n, m, isHunter, isWall, IsBonus);
            *isQuake = 1;
        }
        break;
    case 3:
        if (*fontsize >= maxsize - 3.0f)
        {
            *TextState = 'D';
            if (*TextTimer == -1)
                *TextTimer = 0;
        }
        if (*TextState == 'I')
        {
            *fontsize += speed * GetFrameTime();
        }
        else if ((*TextTimer) >= 2.0)
        {
            *fontsize -= speed * GetFrameTime();
        }
        if (*TextTimer != -1)
            *TextTimer += GetFrameTime();
        char str4[50] = "You can pick and move one hunter!";
        Color color4 = {252, 218, 5, 255};
        Vector2 textSize4 = MeasureTextEx(f, str4, *fontsize, 2);
        Vector2 pos4 = {width / 2, height / 2};
        Vector2 origin4 = {textSize4.x / 2, textSize4.y / 2};
        TextOutline(pos4, origin4, *fontsize, str4, f);
        DrawTextPro(f, str4, pos4, origin4, 0.0f, *fontsize, 2, color4);
        if (*fontsize <= 0.0)
        {
            *TextTimer = -1;
            *TextState = 'I';
            *option = -1;
        }
        break;
    }
}
