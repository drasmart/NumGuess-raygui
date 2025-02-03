//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"
#include "raygui.h"

#include "AimReticle.h"

namespace UI {

void Root::drawScrollPanel(const DrawArea &drawArea) {
    AimReticle().scrollable(
        {
            drawArea.rectangle.width,
            drawArea.rectangle.height,
        },
        scroll)
    ->drawAt( {
        {
            drawArea.rectangle.x + drawArea.rectangle.width / 2,
            drawArea.rectangle.y,
            drawArea.rectangle.width / 2,
            drawArea.rectangle.height,
        },
        drawArea.scale,
    });
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