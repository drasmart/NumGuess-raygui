//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"

#include <iostream>

#include "raygui.h"

#include "AimReticle.h"
#include "Button.h"
#include "GUIScale.h"
#include "TextBox.h"
#include "ValueBox.h"

namespace UI {

void Root::drawScrollPanel(const DrawRequest &drawRequest) {

    demoBox2
    .focusable()
    ->scrollable("SCROLL AREA",
        {
            drawRequest.rectangle.width,
            drawRequest.rectangle.height,
        },
        scroll)
    ->drawAt( drawRequest.child("scroll-panel", {
        drawRequest.rectangle.x + drawRequest.rectangle.width / 2,
        drawRequest.rectangle.y,
        drawRequest.rectangle.width / 2,
        drawRequest.rectangle.height,
    }));
}

void Root::drawScrollPanel2(const DrawRequest &drawRequest) {

    AimReticle().scrollable("SCROLL AREA 2",
        {
            drawRequest.rectangle.width / 4,
            drawRequest.rectangle.height,
        },
        scroll2)
    ->interactable(false)
    ->drawAt( drawRequest.child("scroll-panel-2", {
        drawRequest.rectangle.x + drawRequest.rectangle.width * 5 / 8,
        drawRequest.rectangle.y + drawRequest.rectangle.height / 4,
        drawRequest.rectangle.width / 4,
        drawRequest.rectangle.height / 2,
    }));
}

void Root::drawAt(const DrawRequest &drawRequest) {
    demoBox1
    .focusable()
    ->drawAt(drawRequest);

    drawScrollPanel(drawRequest);
    drawScrollPanel2(drawRequest);

    Button {
        "Test Button",
        [this]() { std::cout << "BTN clicked!" << std::endl; },
    }.toDrawable()->drawAt(drawRequest.child("btn1", {
        drawRequest.rectangle.x + 10,
        drawRequest.rectangle.y + drawRequest.rectangle.height / 2,
        drawRequest.rectangle.width / 3,
        RAYGUI_MESSAGEBOX_BUTTON_HEIGHT,
    }));

    ValueBox {
        text,
        &x,
        -5,
        1000,
        [this]() { std::cout << "ValueBox ENTER! >> " << x << std::endl; },
    }.toDrawable()->padding(8)->drawAt(drawRequest.child("txtBox", {
        drawRequest.rectangle.x + 10,
        drawRequest.rectangle.y + drawRequest.rectangle.height / 2 + RAYGUI_MESSAGEBOX_BUTTON_HEIGHT + 10,
        drawRequest.rectangle.width / 3,
        RAYGUI_MESSAGEBOX_BUTTON_HEIGHT,
    }));
}

} // UI