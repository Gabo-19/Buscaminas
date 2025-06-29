#ifndef JUEGO_H
#define JUEGO_H

#include "raylib.h"
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define COLS 12
#define ROWS 12

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

extern sTile grid[COLS][ROWS];
extern int revealedTilesCount;
extern int minesPresentCount;

extern float timeGameStarted;
extern float timeGameEnded;

extern const char* labelGameWin;
extern const char* labelGameLose;
extern const char* labelEnter;

extern bool isSoundEnabled;
extern bool isMusicEnabled;

#define MAX_TEXTURES 1
typedef enum {
    TEXTURE_FLAG = 0
} texture_asset;

extern Texture2D textures[MAX_TEXTURES];

#define MAX_SOUNDS 3
typedef enum {
    SOUND_CLICK = 0,
    SOUND_EXPLOSION,
    SOUND_PICKUPCOIN
} sound_asset;

extern Sound sounds[MAX_SOUNDS];

#define MAX_MUSIC 1
typedef enum {
    MUSIC_ONE = 0
} music_asset;

extern Music music[MAX_MUSIC];

typedef enum {
    STATE_MAIN_MENU = 0,
    STATE_OPTIONS_MENU,
    STATE_PLAYING,
    STATE_LOSE,
    STATE_WIN
} game_states;

extern game_states gameState;

void GameStartup();
void GameUpdate();
void GameShutdown();
void GameRender();
void GameReset();
void GamePlaySound(int sound);

void ResetTiles();
void RenderTiles();
void RenderTile(sTile tile);
int CountNearbyMines(int col, int row);
bool IsTileIndexValid(int col, int row);
void RevealTile(int col, int row);
void FlagTile(int col, int row);
void RevealTilesFrom(int col, int row);

#endif

