//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include <Engine.h>

#include "IDrawable.h"
#include <functional>
#include <fstream>

namespace Game {

struct Root : UI::IDrawable {
    std::string logFileName = "log.txt";
    std::function<void(const std::string &)> onNameSet;
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
        {
            std::ofstream outfile(logFileName, std::ios_base::app);
            if (!outfile || !outfile.is_open()) {
                return;
            }
            outfile << msg << std::endl;
            outfile.close();
        }
    }
};

} // UI

#endif //ROOT_H
