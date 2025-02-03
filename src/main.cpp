#include "raylib.h"

#include "raygui.h"

#include "UI/Root.h"
#include "UI/GUIScale.h"

#include <sstream>

static const char *title = "raygui - controls test suite";

static void UpdateScale() {
    UI::GuiScale::apply();

    std::stringstream ss;
    ss << title << " (" << UI::GuiScale::guiScale << "x)" << std::endl;
    auto const s = ss.str();
    SetWindowTitle(s.c_str());
}

int main()
{
    const Vector2 modelSize { 500, 300 };
    UI::GuiScale::guiScale = 3;

    Vector2 lastScreenSize {
        modelSize.x * UI::GuiScale::guiScale,
        modelSize.y * UI::GuiScale::guiScale,
    };

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(lastScreenSize.x, lastScreenSize.y, title);

    SetTargetFPS(60);

    UI::GuiScale::init();
    UpdateScale();

    UI::Root root;
    UI::Context context {
        .scale = UI::GuiScale::guiScale,
    };

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
            context.scale = UI::GuiScale::guiScale = (scale.x < scale.y) ? scale.x : scale.y;
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
                newScreenSize.x / UI::GuiScale::guiScale,
                newScreenSize.y / UI::GuiScale::guiScale,
            },
            "root",
            nullptr,
            &context,
        });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
