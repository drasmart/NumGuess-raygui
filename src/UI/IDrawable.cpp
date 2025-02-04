//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "IDrawable.h"

#include "FocusWrapper.h"
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
std::unique_ptr<IDrawable> IDrawable::focusable(bool enabled) {
    return std::make_unique<FocusWrapper>(this, enabled);
}

} // UI
