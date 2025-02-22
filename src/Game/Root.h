//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include "IDrawable.h"

namespace Game {

struct Root : UI::IDrawable {
    Vector2 scroll { 0, 0 };
    char text[64] = "157";
    int x = 13;

    void drawAt(const UI::DrawRequest &drawRequest) override;
};

} // UI

#endif //ROOT_H
