//
// Created by Maksym Kucherov on 22-Feb-25.
//

#include "Label.h"
#include "FuncDrawable.h"
#include "raygui.h"

namespace UI {

    std::unique_ptr<IDrawable> Label::toDrawable() const {
        return std::make_unique<FuncDrawable>([textPtr = text](const DrawRequest& drawRequest) {
            const Rectangle rect = drawRequest.scaledRectangle();
            GuiLabel(rect, textPtr);
        });
    }

    Vector2 Label::estimatedSize(const float scale) const {
        const Vector2 textSizeRaw = MeasureTextEx(
            font,
            text,
            (float)GuiGetStyle(DEFAULT, TEXT_SIZE),
            (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
        const float padding = 1 + scale / 2;
        const Vector2 textSize {
            textSizeRaw.x / scale + padding,
            textSizeRaw.y / scale + padding,
        };
        return textSize;
    }

} // UI
