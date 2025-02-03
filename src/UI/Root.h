//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include "IDrawable.h"

namespace UI {

struct Root : IDrawable {
    bool showMessageBox = false;
    Vector2 scroll { 0, 0 };

    void drawAt(const DrawArea &drawArea) override;
private:
    void drawScrollPanel(const DrawArea &drawArea);
};

} // UI

#endif //ROOT_H
