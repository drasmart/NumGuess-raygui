//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "DemoButtonMsgBox.h"

#include <iostream>

#include "raygui.h"

namespace UI {

void DemoButtonMsgBox::drawAt(const DrawArea &drawArea) {
    if (GuiButton((Rectangle){
        (drawArea.rectangle.x + 24) * drawArea.scale,
        (drawArea.rectangle.y + 24) * drawArea.scale,
        120 * drawArea.scale,
        30 * drawArea.scale,
    }, "#191#Show Message")) {
        std::cout << "SHOW message (";
        drawArea.dumpIds(std::cout);
        std::cout << ")" << std::endl;

        showMessageBox = true;
    }

    if (showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){
            (drawArea.rectangle.x + 85) * drawArea.scale,
            (drawArea.rectangle.y + 70) * drawArea.scale,
            250 * drawArea.scale,
            100 * drawArea.scale,
        },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) {
            std::cout << "HIDE message (";
            drawArea.dumpIds(std::cout);
            std::cout << ")" << std::endl;

            showMessageBox = false;
        }
    }
}

} // UI