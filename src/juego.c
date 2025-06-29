#include "raylib.h"
#include "raymath.h"
#include "juego.h"




void GamePlaySound(int sound) {

    if (isSoundEnabled) {
    PlaySound(sounds[sound]);
    }
}

bool IsTileIndexValid(int col, int row) {
    return (col >= 0 && col < COLS && row >= 0 && row < ROWS);
}

void RevealTilesFrom(int col, int row) {
    for (int colOffset = -1; colOffset <= 1; colOffset++) 
    {
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) 
        {
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
    if (grid[col][row].isFlagged) {
        return; //ya esta marcada
    }

    grid[col][row].isFlagged = !grid[col][row].isFlagged;
    GamePlaySound(SOUND_PICKUPCOIN);

}
void RevealTile(int col, int row) {
    if (grid[col][row].isFlagged || grid[col][row].isRevealed) {
        return; //ya se revelo la casilla o esta marcada
    }

    grid[col][row].isRevealed = true;

    if (grid[col][row].isMine) {
        gameState = STATE_LOSE;
        timeGameEnded = (float)GetTime(); //toma el tiempo hasta perder la partida
        GamePlaySound(SOUND_EXPLOSION);

    }
    else {
        if (grid[col][row].nearbyMineCount == 0) {
            RevealTilesFrom(col, row);
        }

        revealedTilesCount++;

        if (revealedTilesCount >= (ROWS * COLS - minesPresentCount)) {
            gameState = STATE_WIN;
            timeGameEnded = (float)GetTime(); //toma el tiempo hasta ganar la partida
        }
    }
}

int CountNearbyMines(int col, int row) {
    int count = 0;
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
            if (colOffset == 0 && rowOffset  == 0) {
                continue;
            }

            if (grid[col + colOffset][row + rowOffset].isMine) {
                count++;
            }
        }
    }

    return count;
}

void ResetTiles() {

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            grid[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .isMine = false,
                .isRevealed = false,
                .isFlagged = false,
                .nearbyMineCount = -1
            };
        }
    }

    minesPresentCount = (int)(ROWS * COLS * 0.1f);
    int minesToPlace = minesPresentCount;
    while(minesToPlace > 0)
    {
        int col = GetRandomValue(0, COLS);
        int row = GetRandomValue(0, ROWS);

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
        }
        else {
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


void GameStartup() {

    InitAudioDevice();

    Image image1 = LoadImage("assets/flag.png");
    textures[TEXTURE_FLAG] = LoadTextureFromImage(image1);
    UnloadImage(image1);

    sounds[SOUND_CLICK] = LoadSound("assets/click.wav");
    sounds[SOUND_EXPLOSION] = LoadSound("assets/explosion.wav");
    sounds[SOUND_PICKUPCOIN] = LoadSound("assets/pickupCoin.wav");
    music[MUSIC_ONE] = LoadMusicStream("assets/8-bit-game-158815.mp3");

    PlayMusicStream(music[MUSIC_ONE]);

    gameState = STATE_MAIN_MENU;

}

void GameUpdate() {

    UpdateMusicStream(music[MUSIC_ONE]);

    switch (gameState) {
    case STATE_MAIN_MENU:

        if (IsKeyPressed(KEY_N)) { //al pulsar la tecla "N"
            GamePlaySound(SOUND_EXPLOSION);
            GameReset(); 
        }
        else if (IsKeyPressed(KEY_O)) { //al pulsar la tecla "O"
            gameState = STATE_OPTIONS_MENU;
            GamePlaySound(SOUND_EXPLOSION);
        }

        break;

    case STATE_OPTIONS_MENU:

        if (IsKeyPressed(KEY_ENTER)) { //al pulsar la tecla "ENTER"
            gameState = STATE_MAIN_MENU;
            GamePlaySound(SOUND_EXPLOSION);
        }

        if (IsKeyPressed(KEY_S)) { //al pulsar la tecla "S"
            isSoundEnabled = !isSoundEnabled;
            PlaySound(sounds[SOUND_CLICK]);
        }

        if (IsKeyPressed(KEY_M)) { //al pulsar la tecla "M"
            isMusicEnabled = !isMusicEnabled;
            PlaySound(sounds[SOUND_CLICK]);
        if (isMusicEnabled) {
            StopMusicStream(music[MUSIC_ONE]);
            PlayMusicStream(music[MUSIC_ONE]);
        }
        else {
            StopMusicStream(music[MUSIC_ONE]);
        }
    }

        break;

    case STATE_PLAYING:

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int col = (int)(mousePos.x / TILE_WIDTH);
        int row = (int)(mousePos.y / TILE_HEIGHT);

        if(IsTileIndexValid(col, row)) {
            RevealTile(col, row);
            GamePlaySound(SOUND_CLICK);
        }
    } else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        int col = (int)(mousePos.x / TILE_WIDTH);
        int row = (int)(mousePos.y / TILE_HEIGHT);

        if (IsTileIndexValid(col, row)) {
            FlagTile(col, row);
        }
    }
        break;

    case STATE_LOSE:

    if (IsKeyPressed(KEY_ENTER)) { //al pulsar la tecla "ENTER"
        GamePlaySound(SOUND_EXPLOSION);
        gameState = STATE_MAIN_MENU;
    }
        break;

    case STATE_WIN:
    
    if (IsKeyPressed(KEY_ENTER)) { //al pulsar la tecla "ENTER"
        GamePlaySound(SOUND_EXPLOSION);
        gameState = STATE_MAIN_MENU;
    }
        break;
    }

}

void GameRender() {

    int seconds = 0;

    switch (gameState) {
    case STATE_MAIN_MENU:

        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGREEN);
        DrawText("BUSCAMINAS", 20, 20,  40, WHITE); // x=20, y=20, tamano 40 de fuente, color blanco; y asi para los demas
        DrawText("[N]ueva Partida", 120, 220, 20, WHITE);
        DrawText("[O]pciones", 120, 250, 20, WHITE);
        DrawText("ESC para salir", 120, 280, 20, WHITE);
        DrawText("Hecho por @juanpamr06 & @gabo-19", 120, 500, 20, WHITE);
        break;

    case STATE_OPTIONS_MENU:

        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKGREEN);
        DrawText("BUSCAMINAS : : OPCIONES", 20, 20,  40, WHITE);
        DrawText("[S]onido", 120, 220, 20, WHITE);
        if (isSoundEnabled) {
            DrawText("ON", 280, 220, 20, YELLOW);
            DrawText(" / ", 310, 220, 20, WHITE);
            DrawText("OFF", 350, 220, 20, WHITE);
        }
        else {
            DrawText("ON", 280, 220, 20, WHITE);
            DrawText(" / ", 310, 220, 20, WHITE);
            DrawText("OFF", 350, 220, 20, YELLOW);
        }

        DrawText("[M]usica", 120, 250, 20, WHITE);
        if (isMusicEnabled) {
            DrawText("ON", 280, 250, 20, YELLOW);
            DrawText(" / ", 310, 250, 20, WHITE);
            DrawText("OFF", 350, 250, 20, WHITE);
        }
        else {
            DrawText("ON", 280, 250, 20, WHITE);
            DrawText(" / ", 310, 250, 20, WHITE);
            DrawText("OFF", 350, 250, 20, YELLOW);
        }

        break;

    case STATE_PLAYING:
        RenderTiles();
        break;

    case STATE_LOSE:

        RenderTiles();
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8f));
        DrawText(labelGameLose, SCREEN_WIDTH / 2 - MeasureText(labelGameLose, 60) / 2, SCREEN_HEIGHT / 2 - 10, 60, DARKGRAY);
        DrawText(labelEnter, SCREEN_WIDTH / 2 - MeasureText(labelEnter, 34) / 2, (int)(SCREEN_HEIGHT * 0.75f) - 10, 34, DARKGRAY);
        seconds  = (int)(timeGameEnded - timeGameStarted) % 60; //cuenta hasta 60 para saber los segundos totales de la partida al perder
        DrawText(TextFormat("TIEMPO DE JUEGO: %d s", seconds), 20, 40, 34, DARKGRAY);
        break;

    case STATE_WIN:

        RenderTiles();
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8f));
        DrawText(labelGameWin, SCREEN_WIDTH / 2 - MeasureText(labelGameWin, 60) / 2, SCREEN_HEIGHT / 2 - 10, 60, DARKGRAY);
        DrawText(labelEnter, SCREEN_WIDTH / 2 - MeasureText(labelEnter, 34) / 2, (int)(SCREEN_HEIGHT * 0.75f) - 10, 34, DARKGRAY);
        seconds  = (int)(timeGameEnded - timeGameStarted) % 60; //cuenta hasta 60 para saber los segundos totales de la partida al ganar
        DrawText(TextFormat("TIEMPO DE JUEGO: %d s", seconds), 20, 40, 34, DARKGRAY);
        break;
    }
}

void GameShutdown() {

    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(textures[i]);
    }

    for (int i = 0; i < MAX_SOUNDS; i++) {
        UnloadSound(sounds[i]);
    }

    StopMusicStream(music[MUSIC_ONE]);
    UnloadMusicStream(music[MUSIC_ONE]);

    CloseAudioDevice();
}

void GameReset() {

    ResetTiles();
    gameState = STATE_PLAYING;
    revealedTilesCount = 0;

}

