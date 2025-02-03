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

static struct {
    int textSize;
    int scrollBarWidth;
} defaultStyle;

static const char *title = "raygui - controls test suite";

static void UpdateScale() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, defaultStyle.textSize * guiScale);
    GuiSetStyle(DEFAULT, SCROLLBAR_WIDTH, defaultStyle.scrollBarWidth * guiScale);
    GuiSetIconScale(static_cast<int>(guiScale));

    std::stringstream ss;
    ss << title << " (" << guiScale << "x)" << std::endl;
    auto const s = ss.str();
    SetWindowTitle(s.c_str());
}

int main()
{
    const Vector2 modelSize { 500, 300 };
    guiScale = 3;

    Vector2 lastScreenSize {
        modelSize.x * guiScale,
        modelSize.y * guiScale,
    };

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(lastScreenSize.x, lastScreenSize.y, title);

    SetTargetFPS(60);

    defaultStyle = {
        .textSize = GuiGetStyle(DEFAULT, TEXT_SIZE),
        .scrollBarWidth = GuiGetStyle(DEFAULT, SCROLLBAR_WIDTH),
    };
    UpdateScale();

    UI::Root root;

    while (!WindowShouldClose())
    {
        const Vector2 newScreenSize {
            static_cast<float>(GetScreenWidth()),
            static_cast<float>(GetScreenHeight()),
        };
        if (lastScreenSize.x != newScreenSize.x || lastScreenSize.y != newScreenSize.y) {
            const Vector2 scale {
                newScreenSize.x / modelSize.x,
                newScreenSize.y / modelSize.y,
            };
            guiScale = (scale.x < scale.y) ? scale.x : scale.y;
            UpdateScale();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        root.drawAt({
            {
                0,
                0,
                newScreenSize.x / guiScale,
                newScreenSize.y / guiScale,
            },
            guiScale,
        });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
