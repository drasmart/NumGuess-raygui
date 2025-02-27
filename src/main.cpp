#include "raylib.h"

#include "raygui.h"

#include "Root.h"
#include "Context.h"
#include "GUIScale.h"

#include <sstream>
#include <ctime>

static const char *title = "NumGuess";
std::string playerName = "???";

static void UpdateWindowTitle() {
    std::stringstream ss;
    ss << title << " -- " << playerName.c_str() << " (" << UI::GuiScale::guiScale << "x)" << std::endl;
    auto const s = ss.str();
    SetWindowTitle(s.c_str());
}

static void UpdateScale() {
    UI::GuiScale::apply();
    UpdateWindowTitle();
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

    Game::Root root;
    root.logFileName = (std::stringstream() << "game_" << std::time(nullptr) << ".log").str();
    root.onNameSet = [](const std::string &newPlayerName) {
        playerName = newPlayerName;
        UpdateWindowTitle();
    };

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

        context.focusManager.clearCache();

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

        if (!context.focusManager.focusMoved() && IsKeyPressed(KEY_TAB)) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                context.focusManager.movePrev();
            } else {
                context.focusManager.moveNext();
            }
        }
    }

    CloseWindow();
    return 0;
}
