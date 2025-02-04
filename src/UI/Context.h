//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include "raylib.h"
#include <optional>

#include "FocusManager.h"

namespace UI {

struct Context {
    float scale = 1;
    std::optional<Rectangle> clipArea;
    FocusManager focusManager;
};

} // UI

#endif //CONTEXT_H
