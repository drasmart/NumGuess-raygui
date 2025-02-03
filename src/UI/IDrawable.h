//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "ScaledRectangle.h"

namespace UI {

    struct IDrawable {
        virtual void drawAt(const ScaledRectangle &rectangle) = 0;
    };

} // UI

#endif //IDRAWABLE_H
