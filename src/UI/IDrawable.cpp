//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "IDrawable.h"
#include "ScrollWrapper.h"

namespace UI {

IDrawable::~IDrawable() = default;

std::unique_ptr<IDrawable> IDrawable::scrollable(const Vector2 &size, Vector2 &offset) {
    return std::make_unique<ScrollWrapper>(this, size, offset);
}

} // UI
