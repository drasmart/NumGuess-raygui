//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"

namespace UI {

struct ScaledRectangle {
    Rectangle rectangle;
    float scale = 1;
};

} // UI

#endif //SCALEDRECTANGLE_H
