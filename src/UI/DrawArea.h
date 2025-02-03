//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"
#include <optional>

namespace UI {

struct DrawArea {
    Rectangle rectangle;
    float scale = 1;
    std::optional<Rectangle> clipArea;
};

} // UI

#endif //SCALEDRECTANGLE_H
