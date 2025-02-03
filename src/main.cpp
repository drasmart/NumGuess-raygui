#include "raylib.h"

static float guiScale = 1;
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT        24 * guiScale
#define RAYGUI_WINDOWBOX_CLOSEBUTTON_HEIGHT      18 * guiScale
#define RAYGUI_LINE_MARGIN_TEXT  12 * guiScale
#define RAYGUI_LINE_TEXT_PADDING  4 * guiScale
#define RAYGUI_MESSAGEBOX_BUTTON_HEIGHT    24 * guiScale
#define RAYGUI_MESSAGEBOX_BUTTON_PADDING   12 * guiScale
#define RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT      24 * guiScale
#define RAYGUI_TEXTINPUTBOX_BUTTON_PADDING     12 * guiScale
#define RAYGUI_TEXTINPUTBOX_HEIGHT             26 * guiScale
#define ICON_TEXT_PADDING   4 * guiScale
// #define RAYGUI_COLORBARALPHA_CHECKED_SIZE   10 * guiScale
#define RAYGUI_GROUPBOX_LINE_THICK  (int)guiScale
#define RAYGUI_PANEL_BORDER_WIDTH   (int)guiScale
#include "raygui.h"

#include "UI/Root.h"

#include <sstream>

static int defaultTextSize;

static void UpdateScale(float delta) {
    guiScale += delta;
    GuiSetStyle(DEFAULT, TEXT_SIZE, defaultTextSize * guiScale);
    GuiSetIconScale(static_cast<int>(guiScale));
    if (delta) {
        SetWindowSize(400 * guiScale, 200 * guiScale);
    }

    std::stringstream ss;
    ss << "raygui - controls test suite (" << guiScale << "x)" << std::endl;
    auto const s = ss.str();
    SetWindowTitle(s.c_str());
}

int main()
{
    guiScale = 3;

    InitWindow(400 * guiScale, 200 * guiScale, "raygui - controls test suite");
    SetTargetFPS(60);

    defaultTextSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    UpdateScale(0);

    UI::Root root;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_KP_ADD)) {
            UpdateScale(+0.5);
        } else if (IsKeyPressed(KEY_KP_SUBTRACT) && guiScale > 1) {
            UpdateScale(-0.5);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        root.drawAt({
            { 0, 0, 0, 0},
            guiScale,
        });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
