//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "AimReticle.h"
#include "raygui.h"

#include <sstream>

namespace UI {

static void drawHalfSizeRects(const ScaledRectangle &rectangle) {
    DrawRectangle(
        rectangle.rectangle.x * rectangle.scale,
        rectangle.rectangle.y * rectangle.scale,
        rectangle.rectangle.width / 2 * rectangle.scale,
        rectangle.rectangle.height / 2 * rectangle.scale,
        Color(255, 0, 0, 64));
    DrawRectangle(
        (rectangle.rectangle.x + rectangle.rectangle.width / 2) * rectangle.scale,
        (rectangle.rectangle.y + rectangle.rectangle.height / 2) * rectangle.scale,
        rectangle.rectangle.width / 2 * rectangle.scale,
        rectangle.rectangle.height / 2 * rectangle.scale,
        Color(0, 0, 255, 64));
}

static void drawSizeLabel(const ScaledRectangle &rectangle) {
    std::stringstream ss;
    ss
    << "( "
    << rectangle.rectangle.width
    << " , "
    << rectangle.rectangle.height
    << " ) @ "
    << rectangle.scale
    << "x";
    const std::string s = ss.str();
    const Font font = GetFontDefault();
    const Vector2 textSizeRaw = MeasureTextEx(
        font,
        s.c_str(),
        (float)GuiGetStyle(DEFAULT, TEXT_SIZE),
        (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
    const float padding = (int)rectangle.scale + 1;
    const Vector2 textSize {
        textSizeRaw.x / rectangle.scale + padding,
        textSizeRaw.y / rectangle.scale + padding,
    };
    const Rectangle labelRect {
        rectangle.rectangle.x + rectangle.rectangle.width - textSize.x,
        rectangle.rectangle.y + rectangle.rectangle.height - textSize.y,
        textSize.x,
        textSize.y,
    };
    GuiLabel((Rectangle){
        labelRect.x * rectangle.scale,
        labelRect.y * rectangle.scale,
        labelRect.width * rectangle.scale,
        labelRect.height * rectangle.scale,
    }, s.c_str());
}

void AimReticle::drawAt(const ScaledRectangle &rectangle) {
    drawHalfSizeRects(rectangle);
    drawSizeLabel(rectangle);
}

} // UI