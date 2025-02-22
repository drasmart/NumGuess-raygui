//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef VALUEBOX_H
#define VALUEBOX_H

#include "IDrawable.h"

#include <memory>
#include <functional>

namespace UI {

struct ValueBox {
    const char * const text;
    int * const value;
    const int minValue;
    const int maxValue;
    const std::function<void(const DrawRequest &)> onEnter;
    const bool enabled = true;

    [[nodiscard]]
    std::unique_ptr<IDrawable> toDrawable() const;
};

} // UI

#endif //VALUEBOX_H
