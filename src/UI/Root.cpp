//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"
#include "raygui.h"

namespace UI {

void Root::drawAt(const ScaledRectangle rectangle) {
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