#include "raylib.h"
#include "raymath.h"
#include "juego.h"

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
