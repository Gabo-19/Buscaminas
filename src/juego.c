#include "raylib.h"
#include "raymath.h"
#include "juego.h"

const int TILE_WIDTH = SCREEN_WIDTH / COLS;
const int TILE_HEIGHT = SCREEN_HEIGHT / ROWS;

sTile grid[COLS][ROWS];
int revealedTilesCount;
int minesPresentCount;

void GameStartUp() {
    InitAudioDevice();
    GameReset();
}

void GameShutdown() {
    CloseAudioDevice();
}

void GameReset() {
    ResetTiles();
}

void GameUpdate() {
    // aqui aun no se ha agregado nada
}

void GameRender() {
    RenderTiles();
}

int CountNearbyMines(int col, int row) {
    int count = 0;
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
            if (colOffset == 0 && rowOffset == 0) continue;
            int c = col + colOffset;
            int r = row + rowOffset;
            if (c >= 0 && c < COLS && r >= 0 && r < ROWS && grid[c][r].isMine) {
                count++;
            }
        }
    }
    return count;
}

void ResetTiles() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            grid[i][j] = (sTile){ i, j, false, false, false, -1 };
        }
    }

    minesPresentCount = (int)(ROWS * COLS * 0.1f);
    int minesToPlace = minesPresentCount;

    while(minesToPlace > 0) {
        int col = GetRandomValue(0, COLS - 1);
        int row = GetRandomValue(0, ROWS - 1);

        if (!grid[col][row].isMine) {
            grid[col][row].isMine = true;
            minesToPlace--;
        }
    }

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (!grid[i][j].isMine) {
                grid[i][j].nearbyMineCount = CountNearbyMines(i, j);
            }
        }
    }
}

void RenderTile(sTile tile) {
    if (tile.isRevealed) {
        if (tile.isMine) {
            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
        } else {
            DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, LIGHTGRAY);
            if (tile.nearbyMineCount > 0) {
                DrawText(TextFormat("%d", tile.nearbyMineCount), tile.x * TILE_WIDTH + 13, tile.y * TILE_HEIGHT + 4, TILE_HEIGHT - 8, DARKGRAY);
            }
        }
    }

    DrawRectangleLines(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, WHITE);
}

void RenderTiles() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            RenderTile(grid[i][j]);
        }
    }
}

