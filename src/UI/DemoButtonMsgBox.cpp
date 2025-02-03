//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "DemoButtonMsgBox.h"

#include <iostream>

#include "raygui.h"

namespace UI {

void DemoButtonMsgBox::drawAt(const DrawRequest &drawRequest) {
    if (GuiButton((Rectangle){
        (drawRequest.rectangle.x + 24) * drawRequest.scale(),
        (drawRequest.rectangle.y + 24) * drawRequest.scale(),
        120 * drawRequest.scale(),
        30 * drawRequest.scale(),
    }, "#191#Show Message")) {
        std::cout << "SHOW message (";
        drawRequest.dumpIds(std::cout);
        std::cout << ")" << std::endl;

        showMessageBox = true;
    }

    if (showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){
            (drawRequest.rectangle.x + 85) * drawRequest.scale(),
            (drawRequest.rectangle.y + 70) * drawRequest.scale(),
            250 * drawRequest.scale(),
            100 * drawRequest.scale(),
        },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) {
            std::cout << "HIDE message (";
            drawRequest.dumpIds(std::cout);
            std::cout << ")" << std::endl;

            showMessageBox = false;
        }
    }
}

} // UI