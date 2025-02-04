//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "FocusWrapper.h"

#include "AimReticle.h"
#include "Context.h"

namespace UI {

FocusWrapper::FocusWrapper(IDrawable * content, bool focusable):
    content(content),
    focusable(focusable) {}

void FocusWrapper::drawAt(const DrawRequest &drawRequest) {

    bool focused = drawRequest.context->focusManager.checkFocus({
        drawRequest.fullId(),
        drawRequest.rectangle,
    }, focusable);
    content->interactable(focused)->drawAt(drawRequest);
    if (focused) {
        AimReticle().drawAt(drawRequest.child("focus-reticle"));
    }
}

} // UI