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

    void drawAt(const ScaledRectangle &rectangle) override;
private:
    void drawScrollPanel(const ScaledRectangle &rectangle);
};

} // UI

#endif //ROOT_H
