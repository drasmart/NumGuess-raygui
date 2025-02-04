//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "TextBox.h"

#include "FuncDrawable.h"
#include "BoxingDrawable.h"

#include "raygui.h"

namespace UI {

std::unique_ptr<IDrawable> TextBox::toDrawable() const {
    std::unique_ptr<IDrawable> mainFunc = std::make_unique<FuncDrawable>([clone = *this](const DrawRequest &drawRequest){
        const bool focused = drawRequest.checkFocus(clone.enabled);
        if (GuiTextBox(
            drawRequest.scaledRectangle(),
            clone.textBuffer,
            clone.textSize,
            focused))
        {
            drawRequest.context->focusManager.moveNext();
            clone.onEnter();
        }
    });
    std::unique_ptr<IDrawable> decoratedFunc = mainFunc->focusable(enabled);
    return std::make_unique<BoxingDrawable>(decoratedFunc, mainFunc);
}

} // UI