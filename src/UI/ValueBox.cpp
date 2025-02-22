//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "ValueBox.h"

#include "FuncDrawable.h"
#include "BoxingDrawable.h"

#include "raygui.h"

namespace UI {

std::unique_ptr<IDrawable> ValueBox::toDrawable() const {
    std::unique_ptr<IDrawable> mainFunc = std::make_unique<FuncDrawable>([clone = *this](const DrawRequest &drawRequest){
        const bool focused = drawRequest.checkFocus(clone.enabled);
        if (GuiValueBox(
            drawRequest.scaledRectangle(),
            clone.text,
            clone.value,
            clone.minValue,
            clone.maxValue,
            focused))
        {
            if (!focused) {
                drawRequest.claimFocus();
                return;
            }
            clone.onEnter(drawRequest);
            return;
        }
        if (!focused) {
            return;
        }
        if ((*clone.value < 0 && (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_EQUAL)))
            || (*clone.value > 0 && (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)))) {
            *clone.value = -*clone.value;
        }
    });
    std::unique_ptr<IDrawable> decoratedFunc = mainFunc->focusable(enabled);
    return std::make_unique<BoxingDrawable>(decoratedFunc, mainFunc);
}

} // UI