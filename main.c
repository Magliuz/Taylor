#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/bluish/style_bluish.h"
#include "styles/dark/style_dark.h"

#include "tinyexpr.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define MARGIN 25
#define SETTINGS_W    400
#define ERROR_H       175
#define UI_MARGIN 15

Color ThemeColor(int control,int property);
void drawUI();

Rectangle settingsArea;
Rectangle functionGraphArea;
Rectangle errorGraphArea;



int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polinomi di Taylor");
    SetTargetFPS(60);

    GuiLoadStyleBluish();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    settingsArea = (Rectangle){
        MARGIN, MARGIN,
        SETTINGS_W, WINDOW_HEIGHT - 2*MARGIN
    };

    functionGraphArea = (Rectangle){
        settingsArea.x + settingsArea.width + MARGIN, MARGIN,
        WINDOW_WIDTH - settingsArea.width - 3*MARGIN,
        WINDOW_HEIGHT - 3*MARGIN - ERROR_H
    };

    errorGraphArea = (Rectangle){
        functionGraphArea.x,
        functionGraphArea.y + functionGraphArea.height + MARGIN,
        functionGraphArea.width,
        ERROR_H
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(ThemeColor(DEFAULT, BACKGROUND_COLOR));

        GuiGroupBox(settingsArea, "Impostazioni");
        GuiGroupBox(functionGraphArea, "Funzione");
        GuiGroupBox(errorGraphArea, "Errore");
        drawUI();


        EndDrawing();
    }
    CloseWindow();
    return 0;
}

Color ThemeColor(int control,int property) {
    return GetColor(GuiGetStyle(control, property));
}

void drawUI() {
    static bool expressionEdit = false;
    static char expression[128] = "sin(x)";

    Rectangle expressionTextBox = {
        settingsArea.x +UI_MARGIN,
        settingsArea.y + UI_MARGIN + 10,
        settingsArea.width - 2*UI_MARGIN,
        50
    };

    if (GuiTextBox(expressionTextBox, expression, sizeof(expression), expressionEdit)) {
        expressionEdit = !expressionEdit;
    }

    Rectangle okButton = {
        settingsArea.x + UI_MARGIN*3,
        settingsArea.y + settingsArea.height * .7,
        settingsArea.width - 6*UI_MARGIN,
        50
    };

    if (GuiButton(okButton, "OK")) {

    }
}