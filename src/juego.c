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

    Image image1 = LoadImage("assets/flag.png");
    textures[TEXTURE_FLAG] = LoadTextureFromImage(image1);
    UnloadImage(image1);
    GameReset();
}

void GameShutdown() {

    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(textures[i]);
    }
    CloseAudioDevice();
}

void GameReset() {
    ResetTiles();
}

void GameUpdate() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int col = mousePos.x / TILE_WIDTH;
        int row = mousePos.y / TILE_HEIGHT;

        if(IsTileIndexValid(col, row)) {
            RevealTile(col, row);
        }
    } else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        int col = mousePos.x / TILE_WIDTH;
        int row = mousePos.y / TILE_HEIGHT;

        if (IsTileIndexValid(col, row)) {
            FlagTile(col, row);
        }
    }


}

void GameRender() {
    RenderTiles();
}
bool IsTileIndexValid(int col, int row) {
    return (col >= 0 && col < COLS && row >= 0 && row < ROWS);
}

void RevealTilesFrom(int col, int row) {
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
            if (colOffset == 0 && rowOffset == 0) {
                continue; //se salta la casilla actual
            }

            if (!IsTileIndexValid(col + colOffset, row + rowOffset)) {
                continue; //se salta si la casilla no es valida
            }

            RevealTile(col + colOffset, row + rowOffset); //revela la casilla adyacente
        }
    }
}
void FlagTile(int col, int row) {
    grid[col][row].isFlagged {
        return; //ya esta marcada
    }

    grid[col][row].isFlagged = !grid[col][row].isFlagged;


}
void RevealTile(int col, int row) {
    if (grid[col][row].isRevealed || grid[col][row].isFlagged) {
        return; //ya se revelo la casilla o esta marcada
    }

    grid[col][row].isRevealed = true;

    if (grid[col][row].isMine) {
        //game over xd
    } else {
        if (grid[col][row].nearbyMineCount == 0) {
            RevealTilesFrom(col, row);
        }
    
        revealedTilesCount++;
        if (revealedTilesCount >= (ROWS * COLS - minesPresentCount)) {
            //win condition :))))
        }
    } 

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
    } else if (tile.isFlagged) {

        Rectangle source = { 0, 0, (float)textures[TEXTURE_FLAG].width, (float)textures[TEXTURE_FLAG].height };
        Rectangle dest = { (float)(tile.x * TILE_WIDTH), (float)(tile.y * TILE_HEIGHT), (float)TILE_WIDTH, (float)TILE_HEIGHT };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(textures[TEXTURE_FLAG], source, dest, origin, 0.0f, WHITE);

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

