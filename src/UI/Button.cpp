//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "Button.h"

#include "FuncDrawable.h"
#include "BoxingDrawable.h"

#include "raygui.h"

namespace UI {

std::unique_ptr<IDrawable> Button::toDrawable() const {
    std::unique_ptr<IDrawable> mainFunc = std::make_unique<FuncDrawable>([clone = *this](const DrawRequest &drawRequest){
        if (GuiButton(drawRequest.scaledRectangle(), clone.title)) {
            drawRequest.claimFocus();
            clone.callback(drawRequest);
            return;
        }
        if (drawRequest.checkFocus(clone.enabled) && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))) {
            clone.callback(drawRequest);
        }
    });
    std::unique_ptr<IDrawable> decoratedFunc = mainFunc->focusable(enabled);
    return std::make_unique<BoxingDrawable>(decoratedFunc, mainFunc);
}

} // UI