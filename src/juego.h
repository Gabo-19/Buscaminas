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

#define MAX_TEXTURES 1
typedef enum {
	TEXTURE_FLAG = 0
	
} texture_asset;

extern Texture2D textures[MAX_TEXTURES];
extern sTile grid[COLS][ROWS];
extern int revealedTilesCount;
extern int minesPresentCount;



void GameStartUp();
void GameShutdown();
void GameReset();
void GameUpdate();
void GameRender();
void ResetTiles();
void RenderTiles();
void RenderTile(sTile tile);
int CountNearbyMines(int col, int row);
bool IsTileIndexValid(int, int);
void RevealTilesFrom(int, int);
void FlagTile(int, int);
void RevealTile(int, int);

#endif

