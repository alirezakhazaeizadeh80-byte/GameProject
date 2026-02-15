#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "board.h"
#include <stdlib.h>
#include "inputs.h"
#include <math.h>
#include "movements.h"
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "bonus.h"
#include "definitions.h"

/*
 * File: main.c
 * Purpose: Program entry point and main game loop orchestration.
 * Notes: This file wires together initialization, rendering, input, and save/load.
 */

/* Entry point: initialize state, run the render/update loop, and persist game data. */
int main()
{
    srand(time(NULL));
    /* Load or start a new game based on user input. */
    printf("\nWould you like to continue the previous game?(YES: 1, NO: 0): ");
    scanf("%d", &isReturn);
    while (isReturn != 0 && isReturn != 1)
    {
        printf("\033[31mThe input is invlalid!\033[0m\n");
        printf("try again (YES: 1, NO: 0): ");
        scanf("%d", &isReturn);
    }
    FILE *game = fopen("../data/game.dat", "rb");
    ReturnGameBasics(game, &lightCoreH, &lightCoreW, &playersCount, &huntersCount, isReturn, &n, &m, &width, &height, &maxsize, &MaxSize, &cellHeight, &cellWidth);
    ReturnGameDetails(game, isReturn, lightCoreH, lightCoreW, players, hunters, playersCount, huntersCount, walls, n, m, isWall, &BonusCount, isBonus, bonuses, playerMoved, BonusWalls, PlHuDistance, oldHunters, oldPlayers, WallsState, &TempWallcounter, &option, wallTurn, &WallCount, isHunter, &alivePlayers, &counter, dir);
    // SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    /* Window and rendering setup. */
    InitWindow(width, height, "The Tale of the Labyrinth");
    InitAudioDevice();
    SetTargetFPS(60);

    Music music = LoadMusicStream("../assets/audio/music249200.mp3");
    /* Asset loading. */
    LoadPiecesAndFonts(&pieceRed, &pieceBlue, &box, &f, maxsize);

    /* Camera defaults. */
    cam.offset = (Vector2){0, 0};
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;
    PlayMusicStream(music);
    SetMusicVolume(music, 0.5f);
    /* Main loop: update game state and render each frame. */
    while (!WindowShouldClose() || StartFade)
    {
        pathcount = 0;
        UpdateMusicStream(music);
        if(WindowShouldClose() && !StartFade)StartFade = 1;
        if(StartFade){
            if(vul > 0.0){
                vul -= 0.4*GetFrameTime();
                SetMusicVolume(music, vul);
            } else break;
        }

        for (int i = 0; i < huntersCount; i++)
        {
            for (int j = 0; j < alivePlayers; j++)
            {
                PlHuDistance[i][j] = abs(hunters[i][0] - players[j][0]) + abs(hunters[i][1] - players[j][1]);
            }
        }

        ClearBackground(Background);

        /* Scene rendering. */
        BeginDrawing();
        BeginMode2D(cam);
        tempWalls(n, m, cellWidth, cellHeight, BlaWalls);
        PiecesMoving(GameStoppage, cellWidth, cellHeight, &alivePlayers, players, playerMoved, &player, sw, n, m, walls, &WallCount, BonusWalls, &TempWallcounter, isWall, BlaWalls, WallsState, &showError, &counter, &timer, wallTurn, hunters, huntersCount, PlHuDistance, &shakeTimeLeft, BoardQuake, isHunter, dir, isBonus, &cam, shakeIntensity, &shakeOffset, &option, &MovePlayerBonus);

        DrawGridB(n, m, cellWidth, cellHeight, height, width);
        ShowingLightcore(lightCoreH, lightCoreW, cellWidth, cellHeight);

        AnimatePieces(oldPlayers, players, playersCount, 3.0, 0, dir);
        Showingpieces(pieceRed, alivePlayers, oldPlayers, cellWidth, cellHeight, playerMoved, 0, timer, &transparency, &s, player, &PickedHunter, &MovePlayerBonus);

        AnimatePieces(oldHunters, hunters, huntersCount, 3.0, 1, dir);
        Showingpieces(pieceBlue, huntersCount, oldHunters, cellWidth, cellHeight, playerMoved, 1, timer, &transparency, &s, player, &PickedHunter, &MovePlayerBonus);

        ShowingWalls(WallCount, walls, WallsState, cellWidth, cellHeight, wallTurn);
        ShowingBonusBox(box, BonusCount, bonuses, cellWidth, cellHeight);

        EndMode2D();
        CheckBonus(&option, &FontSize, MaxSize, Speed, playerMoved, width, height, f, &TextState, &TextTimer, &TextPrinted, hunters, huntersCount, n, m, isWall, cellWidth, cellHeight, &showError, alivePlayers, players, isBonus, &BonusCount, BonusWalls, &MoveTimer, isHunter, &BoardQuake, bonuses, &counter, &isQuake, &PickedHunter, &HunterX, &HunterY, lightCoreH, lightCoreW, oldHunters, &PickBonusCount, &MovePlayerBonus);
        Win(height, width, lightCoreH, lightCoreW, players, playersCount, f, &fontsize, maxsize, speed, &GameStoppage);
        Lose(height, width, m, players, &alivePlayers, hunters, huntersCount, isHunter, &fontsize, maxsize, speed, f, &GameStoppage, lightCoreH, lightCoreW, oldPlayers, oldHunters, &counter, playerMoved, BonusWalls);

        EndDrawing();
        if(WindowShouldClose() && !StartFade)StartFade = 1;
    }
    UnloadMusicStream(music);
    CloseAudioDevice();

    /* Persist game state on exit. */
    fclose(game);
    SavingGame(&lightCoreH, &lightCoreW, players, hunters, &playersCount, &huntersCount, walls, &n, &m, isWall, &BonusCount, isBonus, bonuses, playerMoved, BonusWalls, PlHuDistance, oldHunters, oldPlayers, WallsState, &TempWallcounter, &option, wallTurn, &WallCount, isHunter, &alivePlayers, &counter);
    return 0;
}
