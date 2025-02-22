//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include "IDrawable.h"

namespace UI {

struct Root : IDrawable {
    Vector2 scroll { 0, 0 };
    char text[64] = "157";
    int x = 13;

    void drawAt(const DrawRequest &drawRequest) override;
private:
    void drawScrollPanel(const DrawRequest &drawRequest);
    void drawScrollPanel2(const DrawRequest &drawRequest);
};

} // UI

#endif //ROOT_H
