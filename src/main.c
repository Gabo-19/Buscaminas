#include "raylib.h"
#include "raymath.h"
#include "juego.h"
    #define SCREEN_WIDTH 600
    #define SCREEN_HEIGHT 600


int main(void) //aqui abre una ventana nada mas por ahora falta hacer las funciones de inicio y renderizado
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Buscaminas proyecto");
    SetTargetFPS(60);
    Iniciarjuego();

    while (!WindowShouldClose())
    {
        Iniciarjuego();
        BeginDrawing();
        ClearBackground(DARKGREEN);

        Render();
        EndDrawing();
    }

    Apagarjuego();
    CloseWindow();
    return 0
}
