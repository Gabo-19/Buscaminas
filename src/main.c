#include "raylib.h"
#include "juego.h"

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 600


int main() //aqui abre una ventana nada mas, por ahora falta hacer las funciones de inicio y renderizado
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Buscaminas proyecto");
    SetTargetFPS(60);
    GameStartUp();

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
