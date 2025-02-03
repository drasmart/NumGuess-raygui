//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include "ScaledRectangle.h"

namespace UI {

struct Root {
    bool showMessageBox = false;

    void drawAt(ScaledRectangle rectangle);
};

} // UI

#endif //ROOT_H
