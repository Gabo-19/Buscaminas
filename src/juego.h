#ifndef JUEGO_H
#define JUEGO_H

#include "raylib.h"
#include <stdbool.h>

#define COLS 12
#define ROWS 12
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;

typedef struct {
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
} sTile;

void GameStartUp();
void GameShutdown();
void GameReset();
void GameUpdate();
void GameRender();
void ResetTiles();
void RenderTiles();
void RenderTile(sTile tile);
int CountNearbyMines(int col, int row);

#endif

