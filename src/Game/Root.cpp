//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"

#include <iostream>
#include <sstream>

#include "raygui.h"

#include "AimReticle.h"
#include "Button.h"
#include "GUIScale.h"
#include "TextBox.h"
#include "ValueBox.h"
#include "DirectionalBox.h"
#include "GuessRangeBar.h"

namespace Game {

using namespace UI;

static void drawScrollPanel(Root &root, const DrawRequest &drawRequest) {

    DirectionalBox {
        .title = "Dir Box",
        .direction = { 0, 1 },
        .offset = root.scroll,
        .insets = { 4, 4 },
        .alignment = 0.5f,
        .count = 5,
        .keys = [](size_t x){ return (int)x; },
        .preferredSizes = [](const DrawRequestIdFragment &idFrag, float mn, const DrawRequest &drawRequest2) {
            return Vector2{
                mn - (float)GuiScale::getRawStyle().scrollBarWidth.listView - 1,
                RAYGUI_MESSAGEBOX_BUTTON_HEIGHT / GuiScale::guiScale,
            };
        },
        .drawers = [](const DrawRequestIdFragment &idFrag, const DrawRequest &btnReq) {
            const auto s = (std::stringstream() << "Boxed Button " << std::get<1>(idFrag)).str();
            Button {
                .title = s.c_str(),
                .callback = [&s](const DrawRequest& btnReq2) {
                    std::cout << s << " Clicked!" << std::endl;
                },
            }.toDrawable()->drawAt(btnReq);
        },
    }
    .toDrawable()
    ->drawAt( drawRequest.child("scroll-panel", {
        drawRequest.rectangle.x + drawRequest.rectangle.width / 2,
        drawRequest.rectangle.y,
        drawRequest.rectangle.width / 2,
        drawRequest.rectangle.height,
    }));
}

void Root::drawAt(const DrawRequest &drawRequest) {
    drawScrollPanel(*this, drawRequest);

    Button {
        "Test Button",
        [this](const DrawRequest &_) { std::cout << "BTN clicked!" << std::endl; },
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
        [this](const DrawRequest &valueBoxDrawRequest) {
            std::cout << "ValueBox ENTER! >> " << x << std::endl;
            valueBoxDrawRequest.dropFocus();
        },
    }.toDrawable()->padding(8)->drawAt(drawRequest.child("txtBox", {
        drawRequest.rectangle.x + 10,
        drawRequest.rectangle.y + drawRequest.rectangle.height / 2 + RAYGUI_MESSAGEBOX_BUTTON_HEIGHT + 10,
        drawRequest.rectangle.width / 3,
        RAYGUI_MESSAGEBOX_BUTTON_HEIGHT,
    }));

    {
        const GuessSession s = {
            .targetNumber = 789,
            .maxValue = 2345,
            //.guesses = { 789 },
            .misses = {
                632,
                901,
            },
        };
        Rectangle r = drawRequest.rectangle;
        r.width /= 3;
        r.x += r.width;
        r.y += r.height / 3;
        GuessRangeBar q { s };
        r.height = q.getHeight(drawRequest.scale());
        q.toDrawable()->drawAt(drawRequest.child("rangeBar", r));
    }
}

} // UI