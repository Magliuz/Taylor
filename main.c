#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/bluish/style_bluish.h"

#include "tinyexpr.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polinomi di Taylor");
    SetTargetFPS(60);

    GuiLoadStyleBluish();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    Rectangle settingsArea = {25, 25, 400, 670};
    Rectangle functionGraphArea = {450, 25, 805, 450};
    Rectangle errorGraphArea = {450, 500, 805, 195};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiGroupBox(settingsArea, "Impostazioni");
        GuiGroupBox(functionGraphArea, "Funzione");
        GuiGroupBox(errorGraphArea, "Errore");

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

