//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "IDrawable.h"
#include "ScrollWrapper.h"
#include "InteractivityWrapper.h"

namespace UI {

IDrawable::~IDrawable() = default;

std::unique_ptr<IDrawable> IDrawable::scrollable(const char *title, const Vector2 &size, Vector2 &offset) {
    return std::make_unique<ScrollWrapper>(title, this, size, offset);
}

std::unique_ptr<IDrawable> IDrawable::interactable(bool interactable) {
    return std::make_unique<InteractivityWrapper>(this, interactable);
}

} // UI
