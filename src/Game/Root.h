//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include <Engine.h>

#include "IDrawable.h"

namespace Game {

struct Root : UI::IDrawable {
    Engine engine;
    std::vector<std::string> chatLog { "Welcome, adventurer!" };
    Vector2 textScroll { 0, 0 };
    Vector2 historyScroll { 0, 0 };
    char nameBuf[64] = "";
    int num = 0;
    bool scrollToBottom = false;

    void drawAt(const UI::DrawRequest &drawRequest) override;
    void say(const std::string &msg) {
        chatLog.push_back(msg);
        scrollToBottom = true;
    }
};

} // UI

#endif //ROOT_H
