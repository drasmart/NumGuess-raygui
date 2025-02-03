//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"
#include "raygui.h"

#include "AimReticle.h"

namespace UI {

void Root::drawScrollPanel(const DrawArea &drawArea) {

    Rectangle view;

    GuiScrollPanel({
            (drawArea.rectangle.x + drawArea.rectangle.width / 2) * drawArea.scale,
            (drawArea.rectangle.y) * drawArea.scale,
            (drawArea.rectangle.width / 2) * drawArea.scale,
            (drawArea.rectangle.height) * drawArea.scale,
        },
    "SCROLL AREA",
{
        drawArea.rectangle.x * drawArea.scale,
        drawArea.rectangle.y * drawArea.scale,
        drawArea.rectangle.width * drawArea.scale,
        drawArea.rectangle.height * drawArea.scale,
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
            (view.x + scroll.x) / drawArea.scale,
            (view.y + scroll.y) / drawArea.scale,
            drawArea.rectangle.width,
            drawArea.rectangle.height,
        },
        .scale = drawArea.scale,
    });

    EndScissorMode();
}

void Root::drawAt(const DrawArea &drawArea) {
    drawScrollPanel(drawArea);

    if (GuiButton((Rectangle){
        24 * drawArea.scale,
        24* drawArea.scale,
        120 * drawArea.scale,
        30 * drawArea.scale,
    }, "#191#Show Message")) showMessageBox = true;

    if (showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){
            85 * drawArea.scale,
            70 * drawArea.scale,
            250 * drawArea.scale,
            100 * drawArea.scale,
        },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) showMessageBox = false;
    }
}

} // UI