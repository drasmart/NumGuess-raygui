//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"
#include "raygui.h"

#include "AimReticle.h"

namespace UI {

void Root::drawScrollPanel(const ScaledRectangle &rectangle) {

    Rectangle view;

    GuiScrollPanel({
            (rectangle.rectangle.x + rectangle.rectangle.width / 2) * rectangle.scale,
            (rectangle.rectangle.y) * rectangle.scale,
            (rectangle.rectangle.width / 2) * rectangle.scale,
            (rectangle.rectangle.height) * rectangle.scale,
        },
    "SCROLL AREA",
{
        rectangle.rectangle.x * rectangle.scale,
        rectangle.rectangle.y * rectangle.scale,
        rectangle.rectangle.width * rectangle.scale,
        rectangle.rectangle.height * rectangle.scale,
    },
    &scroll,
    &view
    );

    DrawRectangle(
        view.x,
        view.y,
        view.width,
        view.height,
        Color(255, 255, 0, 255)
        );

    BeginScissorMode(
        view.x,
        view.y,
        view.width,
        view.height);

    AimReticle().drawAt({
        .rectangle = {
            (view.x + scroll.x) / rectangle.scale,
            (view.y + scroll.y) / rectangle.scale,
            rectangle.rectangle.width,
            rectangle.rectangle.height,
        },
        .scale = rectangle.scale,
    });

    EndScissorMode();
}

void Root::drawAt(const ScaledRectangle &rectangle) {
    drawScrollPanel(rectangle);

    if (GuiButton((Rectangle){
        24 * rectangle.scale,
        24* rectangle.scale,
        120 * rectangle.scale,
        30 * rectangle.scale,
    }, "#191#Show Message")) showMessageBox = true;

    if (showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){
            85 * rectangle.scale,
            70 * rectangle.scale,
            250 * rectangle.scale,
            100 * rectangle.scale,
        },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) showMessageBox = false;
    }
}

} // UI