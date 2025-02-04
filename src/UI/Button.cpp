//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "Button.h"

#include "FuncDrawable.h"

#include "raygui.h"

namespace UI {

std::unique_ptr<IDrawable> Button::toDrawable() const {
    return std::make_unique<FuncDrawable>([clone = *this](const DrawRequest &drawRequest){
        if (GuiButton(drawRequest.scaledRectangle(), clone.title)) {
            drawRequest.claimFocus();
            clone.callback();
            return;
        }
        if (drawRequest.checkFocus(clone.enabled) && (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE))) {
            clone.callback();
        }
    })->focusable(enabled);
}

} // UI