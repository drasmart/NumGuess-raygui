//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "FocusWrapper.h"

#include "AimReticle.h"

namespace UI {

FocusWrapper::FocusWrapper(IDrawable * content, bool focusable):
    content(content),
    focusable(focusable) {}

void FocusWrapper::drawAt(const DrawRequest &drawRequest) {

    const bool focused = drawRequest.context->focusManager.checkFocus(
        drawRequest.toFocusable(), focusable);
    content->interactable(focusable)->drawAt(drawRequest);
    if (focused) {
        AimReticle().drawAt(drawRequest.child("focus-reticle"));
    }
}

} // UI