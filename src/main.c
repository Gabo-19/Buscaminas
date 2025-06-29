#include "raylib.h"
#include "raymath.h"
#include "juego.h"

const int TILE_WIDTH = SCREEN_WIDTH / COLS;
const int TILE_HEIGHT = SCREEN_HEIGHT / ROWS;

sTile grid[COLS][ROWS];
int revealedTilesCount = 0;
int minesPresentCount = 0;

float timeGameStarted = 0;
float timeGameEnded = 0;

const char* labelGameWin = "GANASTE! :D";
const char* labelGameLose = "PERDISTE! :C";
const char* labelEnter = "PULSE ENTER PARA ACCEDER AL MENU PRINCIPAL";

bool isSoundEnabled = true;
bool isMusicEnabled = true;

Texture2D textures[MAX_TEXTURES];
Sound sounds[MAX_SOUNDS];
Music music[MAX_MUSIC];

game_states gameState = STATE_MAIN_MENU;


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Buscaminas proyecto");
    SetTargetFPS(60);
    GameStartup();

    while (!WindowShouldClose())
    {
        GameUpdate();
        BeginDrawing();
        ClearBackground(DARKGREEN);

        GameRender();
        EndDrawing();
    }

    GameShutdown();
    CloseWindow();

    return 0;
}
