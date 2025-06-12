#include "raylib.h"
#include "raymath.h"
#include "juego.h"

    #define SCREEN_WIDTH 600
    #define SCREEN_HEIGHT 600
    #define COLS 12
    #define ROWS 12


const int TILE_WIDTH = SCREEN_WIDTH / COLS;
const int TILE_HEIGHT = SCREEN_HEIGHT / ROWS;

void Iniciarjuego();{
 InitAudioDevice();
}

void Apagarjuego(void);{
 CloseAudioDevice();
}
void Reiniciarjuego(void); {

}
void Render(); {
}

