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
Vector2 findRectangleCenter(Rectangle rectangle);
double determineValueOfX(double scale,  int position_x, int center_x, int offset_x);
double determineValueOfY(double scale, double y, int center_y, int offset_y);
void drawGraph(Vector2 center, Vector2 offset, double scale, int width, int height);

Rectangle settingsArea, functionGraphArea, errorGraphArea;
Vector2 functionGraphCenter, errorGraphCenter;

double x;
te_variable vars[] = {{"x", &x}};
te_expr *function;

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

        drawGraph(findRectangleCenter(functionGraphArea), (Vector2){0,0}, 0.05, functionGraphArea.width, functionGraphArea.height);

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
    static int err;
    static bool expressionError = false;

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
        te_expr *temporaryFunction = te_compile(expression, vars, 1, &err);
        if (temporaryFunction) {
            function = temporaryFunction;
            expressionError = false;
        }else {
            expressionError = true;
        }
    }

    if (expressionError) {
        Color errorTextColor = ThemeColor(DEFAULT, TEXT_COLOR_FOCUSED);
        Vector2 errorTextPosition = {expressionTextBox.x, expressionTextBox.y + okButton.height + 5};
        const char *errorTextText = TextFormat("Errore in posizione: %d", err);
        DrawText(errorTextText, errorTextPosition.x, errorTextPosition.y, 20, errorTextColor);
    }

}

Vector2 findRectangleCenter(Rectangle rectangle) {
    return (Vector2){rectangle.x + rectangle.width/2, rectangle.y + rectangle.height/2};
}

void drawGraph(Vector2 center, Vector2 offset, double scale, int width, int height) {
    int leftGraphBorder = center.x - width/2;
    int rightGraphBorder = center.x + width/2;

    x = determineValueOfX(scale, leftGraphBorder, center.x, offset.x);
    int y = determineValueOfY(scale, te_eval(function), center.y, offset.y);
    Vector2 previousPoint = {leftGraphBorder, y};
    Vector2 nextPoint = {0,0};

    for (int i= leftGraphBorder + 1; i <= rightGraphBorder; i++) {
        x = determineValueOfX(scale, i, center.x, offset.x);
        y = determineValueOfY(scale, te_eval(function), center.y, offset.y);

        nextPoint = (Vector2){i, y};
        DrawLineEx(previousPoint, nextPoint, 4, ThemeColor(DEFAULT, LINE_COLOR));
        previousPoint = nextPoint;
    }
}

double determineValueOfX(double scale, int position_x, int center_x, int offset_x) {
    return (position_x - center_x + offset_x)*scale;
}

double determineValueOfY(double scale, double y, int center_y, int offset_y) {
    return (center_y - y/scale - offset_y);
}