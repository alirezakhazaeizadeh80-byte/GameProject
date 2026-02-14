#include "movements.h"
#include "raylib.h"
#include <stdbool.h>
#include "bonus.h"
#include "pathfinding.h"
#include "board.h"

/*
 * File: movements.c
 * Purpose: Player/hunter movement, animation, and endgame checks.
 */

/* Check whether a player occupies the given grid cell. */
int isPlayer(int players[][2], int alivePlayers, int x, int y)
{
    for (int i = 0; i < alivePlayers; i++)
    {
        if (players[i][0] == x && players[i][1] == y)
            return 1;
    }
    return 0;
}
/* Attempt to move a player in a direction, setting an error if blocked. */
void movePieces(int rows, int cols, int players[][2], int player, int walls[][2], char wallsstates[], int wallcount, char move, int *showerror, int isWall[][15][2], int alivePlayers, int isHunter[][15])
{
    if (player == -1)
        return;
    int px = players[player][0];
    int py = players[player][1];
    if (move == 'W' && (px <= 0 || isWall[px - 1][py][0] == 1 || isPlayer(players, alivePlayers, px - 1, py) || isHunter[px - 1][py] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'W')
    {
        players[player][0] -= 1;
    }
    if (move == 'A' && (py <= 0 || isWall[px][py - 1][1] == 1 || isPlayer(players, alivePlayers, px, py - 1) || isHunter[px][py - 1] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'A')
    {
        players[player][1] -= 1;
    }
    if (move == 'S' && (px >= (rows - 1) || isWall[px][py][0] == 1 || isPlayer(players, alivePlayers, px + 1, py) || isHunter[px + 1][py] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'S')
    {
        players[player][0] += 1;
    }
    if (move == 'D' && (py >= (cols - 1) || isWall[px][py][1] == 1 || isPlayer(players, alivePlayers, px, py + 1) || isHunter[px][py + 1] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'D')
    {
        players[player][1] += 1;
    }
}

/* Find the nearest non-ignored player for a hunter. */
int searchNearestPlayer(int hunter, int alivePlayers, int huntersCount, int PlHuDistance[][15], int ignore[])
{
    int min = 30;
    int ans = -1;
    for (int i = 0; i < alivePlayers; i++)
    {
        if (ignore[i] == 1)
            continue;
        if (PlHuDistance[hunter][i] < min)
        {
            min = PlHuDistance[hunter][i];
            ans = i;
        }
    }
    return ans;
}

/* Update hunter positions based on distance and wall constraints. */
void updateHunters(int n, int m, int hunters[][2], int huntersCount, int players[][2], int alivePlayers, int PlHuDistance[][15], int isWall[][15][2], int isHunter[][15], int dir[])
{
    int moved = 0;
    int ignore[alivePlayers];
    for (int j = 0; j < alivePlayers; j++)
        ignore[j] = 0;
    for (int i = 0; i < huntersCount; i++)
    {
        moved = 0;
        int player = searchNearestPlayer(i, alivePlayers, huntersCount, PlHuDistance, ignore);
        if (player == -1)
        { // means no player that hunter gets nearer to it
            for (int j = 0; j < alivePlayers; j++)
                ignore[j] = 0; // modify ignore[] for next hunter
            continue;
        }
        int px = players[player][0];
        int py = players[player][1];
        int hx = hunters[i][0];
        int hy = hunters[i][1];
        if (hy > 1 && hy - py > 1 && isWall[hx][hy - 1][1] == 0 && isWall[hx][hy - 2][1] == 0 && isHunter[hx][hy - 2] == 0)
        {
            isHunter[hx][hy] = 0;
            isHunter[hx][hy - 2] = 1;
            hunters[i][1] -= 2;
            moved = 2;
            dir[i] = -1;
        }
        else if (hy < m - 2 && hy - py < -1 && isWall[hx][hy][1] == 0 && isWall[hx][hy + 1][1] == 0 && isHunter[hx][hy + 2] == 0)
        {
            isHunter[hx][hy] = 0;
            isHunter[hx][hy + 2] = 1;
            hunters[i][1] += 2;
            moved = 2;
            dir[i] = -1;
        }
        else if (hy > 0 && hy - py > 0 && isWall[hx][hy - 1][1] == 0 && isHunter[hx][hy - 1] == 0)
        {
            isHunter[hx][hy] = 0;
            isHunter[hx][hy - 1] = 1;
            hunters[i][1] -= 1;
            moved = 1;
            dir[i] = -1;
            if (hx > 0 && hx - px > 0 && isWall[hx - 1][hy - 1][0] == 0 && isHunter[hx - 1][hy - 1] == 0)
            {
                isHunter[hx][hy - 1] = 0;
                isHunter[hx - 1][hy - 1] = 1;
                hunters[i][0] -= 1;
                moved = 2;
                dir[i] = 0;
            }
            else if (hx < n - 1 && hx - px < 0 && isWall[hx][hy - 1][0] == 0 && isHunter[hx + 1][hy - 1] == 0)
            {
                isHunter[hx][hy - 1] = 0;
                isHunter[hx + 1][hy - 1] = 1;
                hunters[i][0] += 1;
                moved = 2;
                dir[i] = 0;
            }
        }
        else if (hy < m - 1 && hy - py < 0 && isWall[hx][hy][1] == 0 && isHunter[hx][hy + 1] == 0)
        {
            isHunter[hx][hy] = 0;
            isHunter[hx][hy + 1] = 1;
            hunters[i][1] += 1;
            moved = 1;
            dir[i] = -1;
            if (hx > 0 && hx - px > 0 && isWall[hx - 1][hy + 1][0] == 0 && isHunter[hx - 1][hy + 1] == 0)
            {
                isHunter[hx][hy + 1] = 0;
                isHunter[hx - 1][hy + 1] = 1;
                hunters[i][0] -= 1;
                moved = 2;
                dir[i] = 0;
            }
            else if (hx < n - 1 && hx - px < 0 && isWall[hx][hy + 1][0] == 0 && isHunter[hx + 1][hy + 1] == 0)
            {
                isHunter[hx][hy + 1] = 0;
                isHunter[hx + 1][hy + 1] = 1;
                hunters[i][0] += 1;
                moved = 2;
                dir[i] = 0;
            }
        }
        if (moved != 2)
        { // check for a better movement
            if (hx > 1 && hx - px > 1 && isWall[hx - 1][hy][0] == 0 && isWall[hx - 2][hy][0] == 0 && isHunter[hx - 2][hy] == 0)
            {
                if (moved == 1)
                {
                    isHunter[hunters[i][0]][hunters[i][1]] = 0;
                    hunters[i][0] = hx;
                    hunters[i][1] = hy;
                }
                isHunter[hx][hy] = 0;
                isHunter[hx - 2][hy] = 1;
                hunters[i][0] -= 2;
                moved = 2;
                dir[i] = -1;
            }
            else if (hx < n - 2 && hx - px < -1 && isWall[hx][hy][0] == 0 && isWall[hx + 1][hy][0] == 0 && isHunter[hx + 2][hy] == 0)
            {
                if (moved == 1)
                {
                    isHunter[hunters[i][0]][hunters[i][1]] = 0;
                    hunters[i][0] = hx;
                    hunters[i][1] = hy;
                }
                isHunter[hx][hy] = 0;
                isHunter[hx + 2][hy] = 1;
                hunters[i][0] += 2;
                moved = 2;
                dir[i] = -1;
            }
            else if (hx > 0 && hx - px > 0 && isWall[hx - 1][hy][0] == 0 && isHunter[hx - 1][hy] == 0)
            {

                if (hy < m - 1 && hy - py < 0 && isWall[hx - 1][hy][1] == 0 && isHunter[hx - 1][hy + 1] == 0)
                {
                    if (moved == 1)
                    {
                        isHunter[hunters[i][0]][hunters[i][1]] = 0;
                        hunters[i][0] = hx;
                        hunters[i][1] = hy;
                    }
                    isHunter[hx][hy] = 0;
                    isHunter[hx - 1][hy + 1] = 1;
                    hunters[i][0] -= 1;
                    hunters[i][1] += 1;
                    moved = 2;
                    dir[i] = 1;
                }
                else if (hy > 0 && hy - py > 0 && isWall[hx - 1][hy - 1][1] == 0 && isHunter[hx - 1][hy - 1] == 0)
                {
                    if (moved == 1)
                    {
                        isHunter[hunters[i][0]][hunters[i][1]] = 0;
                        hunters[i][0] = hx;
                        hunters[i][1] = hy;
                    }
                    isHunter[hx][hy] = 0;
                    isHunter[hx - 1][hy - 1] = 1;
                    hunters[i][0] -= 1;
                    hunters[i][1] -= 1;
                    moved = 2;
                    dir[i] = 1;
                }
                else if (moved == 0)
                {
                    isHunter[hx][hy] = 0;
                    isHunter[hx - 1][hy] = 1;
                    hunters[i][0] -= 1;
                    moved = 1;
                    dir[i] = -1;
                }
            }
            else if (hx < n - 1 && hx - px < 0 && isWall[hx][hy][0] == 0 && isHunter[hx + 1][hy] == 0)
            {

                if (hy < m - 1 && hy - py < 0 && isWall[hx + 1][hy][1] == 0 && isHunter[hx + 1][hy + 1] == 0)
                {
                    if (moved == 1)
                    { // ignore previous horizental movement
                        isHunter[hunters[i][0]][hunters[i][1]] = 0;
                        hunters[i][0] = hx;
                        hunters[i][1] = hy;
                    }
                    isHunter[hx][hy] = 0;
                    isHunter[hx + 1][hy + 1] = 1;
                    hunters[i][0] += 1;
                    hunters[i][1] += 1;
                    moved = 2;
                    dir[i] = 1;
                }
                else if (hy > 0 && hy - py > 0 && isWall[hx + 1][hy - 1][1] == 0 && isHunter[hx + 1][hy - 1] == 0)
                {
                    if (moved == 1)
                    {
                        isHunter[hunters[i][0]][hunters[i][1]] = 0;
                        hunters[i][0] = hx;
                        hunters[i][1] = hy;
                    }
                    isHunter[hx][hy] = 0;
                    isHunter[hx + 1][hy - 1] = 1;
                    hunters[i][0] += 1;
                    hunters[i][1] -= 1;
                    moved = 2;
                    dir[i] = 1;
                }
                else if (moved == 0)
                {
                    isHunter[hx][hy] = 0;
                    isHunter[hx + 1][hy] = 1;
                    hunters[i][0] += 1;
                    moved = 1;
                    dir[i] = -1;
                }
            }
        }
        if (moved == 0)
        {
            ignore[player] = 1;
            i--; // update this hunter again
        }
        else
        {
            for (int j = 0; j < alivePlayers; j++)
                ignore[j] = 0;
        }
    }
}
/* Draw the win screen if any player reaches the lightcore. */
void Win(int height, int width, int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed, int *GameStoppage)
{
    for (int i = 0; i < playerCount; i++)
    {
        if (players[i][0] == lightcoreX && players[i][1] == lightcoreY)
        {
            if (*fontsize < maxsize)
            {
                *fontsize += speed * GetFrameTime();
            }
            char str[15] = "You Won!";
            Color color = {0, 194, 50, 255};

            Vector2 textSize = MeasureTextEx(f, str, *fontsize, 2);
            Vector2 pos = {width / 2, height / 2};
            Vector2 origin = {textSize.x / 2, textSize.y / 2};
            TextOutline(pos, origin, *fontsize, str, f);
            DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
            *GameStoppage = 1;
        }
    }
}

/* Draw the lose screen and remove captured players. */
void Lose(int height, int width, int cols, int players[][2], int *alivePlayers, int hunters[][2], int huntersCount, int isHunter[][15], float *fontsize, float maxsize, float speed, Font f, int *GameStoppage, int LightcoreH, int LightcoreW, float oldPlayers[][2], float oldHunters[][2], int *counter, int playerMoved[])
{
    for (int i = 0; i < *alivePlayers; i++)
    {
        int px = players[i][0];
        int py = players[i][1];
        if (isHunter[px][py] == 1 && (px != LightcoreH || py != LightcoreW))
        {
            if (*alivePlayers == 1)
            {
                if (*fontsize < maxsize)
                {
                    *fontsize += speed * GetFrameTime();
                }

                char str[15] = "You Lost!";

                Color color = {255, 0, 0, 255};
                Vector2 textSize = MeasureTextEx(f, str, *fontsize, 2);
                Vector2 pos = {width / 2, height / 2};
                Vector2 origin = {textSize.x / 2, textSize.y / 2};
                TextOutline(pos, origin, *fontsize, str, f);
                DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
                *GameStoppage = 1;
            }
            else
            {
                int ind = FindIndex(hunters, huntersCount, px, py);
                if (fabs(oldHunters[ind][0] - hunters[ind][0]) <= 0.02 && fabs(oldHunters[ind][1] - hunters[ind][1]) <= 0.02)
                {
                    if (*counter != 0 && playerMoved[i] == 1)
                        (*counter) -= 1; // for board quake bonus
                    for (int j = i + 1; j < *alivePlayers; j++)
                    {
                        players[j - 1][0] = players[j][0];
                        players[j - 1][1] = players[j][1];
                        playerMoved[j - 1] = playerMoved[j];
                    }
                    for (int k = 0; k < *alivePlayers; k++)
                    {
                        oldPlayers[k][0] = (float)players[k][0];
                        oldPlayers[k][1] = (float)players[k][1];
                    }
                    (*alivePlayers) -= 1;
                }
            }
        }
    }
}
/* Interpolate piece positions for smooth movement. */
void AnimatePieces(float old[][2], int pieces[][2], int piecesCount, float speed, int state, int dir[])
{
    float targetX, targetY;
    for (int i = 0; i < piecesCount; i++)
    {
        targetX = (float)pieces[i][0];
        targetY = (float)pieces[i][1];
        if (state == 1)
        {
            if (dir[i] == 0)
            {
                if (fabsf(old[i][1] - targetY) > 0.02f)
                {
                    if (old[i][1] < (float)pieces[i][1])
                        old[i][1] += speed * GetFrameTime();
                    else if (old[i][1] > (float)pieces[i][1])
                        old[i][1] -= speed * GetFrameTime();
                }
                else
                {
                    old[i][1] = targetY;
                    if (fabsf(old[i][0] - targetX) > 0.02f)
                    {
                        if (old[i][0] < (float)pieces[i][0])
                            old[i][0] += speed * GetFrameTime();
                        else if (old[i][0] > (float)pieces[i][0])
                            old[i][0] -= speed * GetFrameTime();
                    }
                    else
                    {
                        old[i][0] = targetX;
                    }
                }
            }
            else
            {
                if (fabsf(old[i][0] - targetX) > 0.02f)
                {
                    if (old[i][0] < (float)pieces[i][0])
                        old[i][0] += speed * GetFrameTime();
                    else if (old[i][0] > (float)pieces[i][0])
                        old[i][0] -= speed * GetFrameTime();
                }
                else
                {
                    old[i][0] = targetX;
                    if (fabsf(old[i][1] - targetY) > 0.02f)
                    {
                        if (old[i][1] < (float)pieces[i][1])
                            old[i][1] += speed * GetFrameTime();
                        else if (old[i][1] > (float)pieces[i][1])
                            old[i][1] -= speed * GetFrameTime();
                    }
                    else
                    {
                        old[i][1] = targetY;
                    }
                }
            }
        }
        else
        {
            if (fabsf(old[i][1] - targetY) > 0.02f)
            {
                if (old[i][1] < (float)pieces[i][1])
                    old[i][1] += speed * GetFrameTime();
                else if (old[i][1] > (float)pieces[i][1])
                    old[i][1] -= speed * GetFrameTime();
            }
            else
            {
                old[i][1] = targetY;
                if (fabsf(old[i][0] - targetX) > 0.02f)
                {
                    if (old[i][0] < (float)pieces[i][0])
                        old[i][0] += speed * GetFrameTime();
                    else if (old[i][0] > (float)pieces[i][0])
                        old[i][0] -= speed * GetFrameTime();
                }
                else
                {
                    old[i][0] = targetX;
                }
            }
        }
    }
}

/* Handle player input, wall placement, hunter updates, and screen shake. */
void PiecesMoving(int GameStoppage, float cellWidth, float cellHeight, int *alivePlayers, int players[][2], int playerMoved[], int *player, int sw, int n, int m, int walls[][2], int *WallCount, int BonusWalls[], int *TempWallcounter, int isWall[][15][2], Rectangle BlaWalls[][15][2], char WallsState[], int *showError, int *counter, float *timer, int wallTurn[], int hunters[][2], int huntersCount, int PlHuDistance[][15], float *shakeTimeLeft, int BoardQuake, int isHunter[][15], int dir[], int isBonus[][15], Camera2D *cam, float shakeIntensity, Vector2 *shakeOffset, int *option, int *MovePlayerBonus)
{
    if (GameStoppage == 0)
    {
        // int PlayerSelected = 0;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(IsKeyDown(KEY_T)))
        {
            int x = GetMouseX();
            int y = GetMouseY();
            int cellX = (x) / cellWidth;
            int cellY = (y) / cellHeight;
            for (int i = 0; i < (*alivePlayers); i++)
            {
                if (players[i][1] == cellX && players[i][0] == cellY && playerMoved[i] == 0)
                {
                    *player = i;
                    sw = 1;
                    // PlayerSelected = 1;
                    break;
                }
            }

            if (sw == 0)
                *player = -1;
            sw = 0;
        }
        if (IsKeyDown(KEY_T))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mousePos = GetMousePosition();
                if (*player != -1 && BonusWalls[*player] > 0)
                {
                    if (ShowingTempWalls(n, m, walls, WallCount, WallsState, TempWallcounter, isWall, mousePos, BlaWalls, wallTurn, 1, BonusWalls, *player) == 1)
                    {
                        playerMoved[*player] = 1;
                    }
                }
                if ((*TempWallcounter) > 0 && *player != -1 && playerMoved[*player] == 0)
                {
                    if (ShowingTempWalls(n, m, walls, WallCount, WallsState, TempWallcounter, isWall, mousePos, BlaWalls, wallTurn, 0, BonusWalls, *player) == 1)
                    {
                        playerMoved[*player] = 1;
                    }
                }
            }
            Vector2 mousePos = GetMousePosition();

            showTempWall(mousePos, n, m, cellWidth, cellHeight, isWall, BlaWalls);
        }
        if ((*player) != -1 && playerMoved[*player] == 0)
        {
            if (IsKeyPressed(KEY_W))
            {
                movePieces(n, m, players, *player, walls, WallsState, *WallCount, 'W', showError, isWall, *alivePlayers, isHunter);
                if (*showError == 0)
                {
                    playerMoved[*player] = 1;
                    if (*MovePlayerBonus != -1)
                        *MovePlayerBonus = -1;
                }
            }
            else if (IsKeyPressed(KEY_A))
            {
                movePieces(n, m, players, *player, walls, WallsState, *WallCount, 'A', showError, isWall, *alivePlayers, isHunter);
                if (*showError == 0)
                {
                    playerMoved[*player] = 1;
                    if (*MovePlayerBonus != -1)
                        *MovePlayerBonus = -1;
                }
            }
            else if (IsKeyPressed(KEY_S))
            {
                movePieces(n, m, players, *player, walls, WallsState, *WallCount, 'S', showError, isWall, *alivePlayers, isHunter);
                if (*showError == 0)
                {
                    playerMoved[*player] = 1;
                    if (*MovePlayerBonus != -1)
                        *MovePlayerBonus = -1;
                }
            }
            else if (IsKeyPressed(KEY_D))
            {
                movePieces(n, m, players, *player, walls, WallsState, *WallCount, 'D', showError, isWall, *alivePlayers, isHunter);
                if (*showError == 0)
                {
                    playerMoved[*player] = 1;
                    if (*MovePlayerBonus != -1)
                        *MovePlayerBonus = -1;
                }
            }
            else if (IsKeyPressed(KEY_SPACE))
            {
                if (*showError == 0)
                {
                    playerMoved[*player] = 1;
                    if (*MovePlayerBonus != -1)
                        *MovePlayerBonus = -1;
                }
            }
        }
        if ((*player) != -1 && playerMoved[*player] == 1)
        {
            (*counter)++;
            *player = -1;
        }

        if ((*counter) == (*alivePlayers) && (*option) != 2)
        {
            if ((*timer) == -1)
            {
                (*timer) = 0;
            }
        }
        if ((*timer) != -1 && *MovePlayerBonus == -1)
            (*timer) += GetFrameTime();
        if ((*timer) >= 0.4 && (*option) != 2 && *MovePlayerBonus == -1)
        { // related to board quake bonus

            (*counter) = 0;
            for (int i = 0; i < (*alivePlayers); i++)
                playerMoved[i] = 0;
            for (int i = (*WallCount) - 1; wallTurn[i] > 0; i--)
            {
                wallTurn[i]--;
                int state;
                if (WallsState[i] == 'H')
                    state = 0;
                else if (WallsState[i] == 'V')
                    state = 1;
                if (wallTurn[i] == 0)
                    isWall[walls[i][0]][walls[i][1]][state] = 0;
            }
            for (int i = 0; i < huntersCount; i++)
            {
                for (int j = 0; j < (*alivePlayers); j++)
                {
                    PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
                }
            }

            updateHunters(n, m, hunters, huntersCount, players, *alivePlayers, PlHuDistance, isWall, isHunter, dir);

            *timer = -1;
        }
        if ((*showError) == 1)
        {
            (*shakeTimeLeft) = 0.2f;
            *showError = 0;
        }
        if ((*shakeTimeLeft) > 0)
        {
            (*shakeTimeLeft) -= GetFrameTime();

            (*shakeOffset).x = GetRandomValue(-shakeIntensity, shakeIntensity);
            (*shakeOffset).y = GetRandomValue(-shakeIntensity, shakeIntensity);
        }
        if (BoardQuake == 1)
        {
            (*shakeOffset).x = GetRandomValue(-shakeIntensity, shakeIntensity);
            (*shakeOffset).y = GetRandomValue(-shakeIntensity, shakeIntensity);
        }
        (*cam).offset = (*shakeOffset);
    }
}
