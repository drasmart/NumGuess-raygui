//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "AimReticle.h"
#include "raygui.h"

#include <sstream>

namespace UI {

static void drawHalfSizeRects(const DrawArea &drawArea) {
    DrawRectangle(
        drawArea.rectangle.x * drawArea.scale,
        drawArea.rectangle.y * drawArea.scale,
        drawArea.rectangle.width / 2 * drawArea.scale,
        drawArea.rectangle.height / 2 * drawArea.scale,
        Color(255, 0, 0, 64));
    DrawRectangle(
        (drawArea.rectangle.x + drawArea.rectangle.width / 2) * drawArea.scale,
        (drawArea.rectangle.y + drawArea.rectangle.height / 2) * drawArea.scale,
        drawArea.rectangle.width / 2 * drawArea.scale,
        drawArea.rectangle.height / 2 * drawArea.scale,
        Color(0, 0, 255, 64));
}

static void drawSizeLabel(const DrawArea &drawArea) {
    std::stringstream ss;
    ss
    << "( "
    << drawArea.rectangle.width
    << " , "
    << drawArea.rectangle.height
    << " ) @ "
    << drawArea.scale
    << "x";
    const std::string s = ss.str();
    const Font font = GetFontDefault();
    const Vector2 textSizeRaw = MeasureTextEx(
        font,
        s.c_str(),
        (float)GuiGetStyle(DEFAULT, TEXT_SIZE),
        (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
    const float padding = (int)drawArea.scale + 1;
    const Vector2 textSize {
        textSizeRaw.x / drawArea.scale + padding,
        textSizeRaw.y / drawArea.scale + padding,
    };
    const Rectangle labelRect {
        drawArea.rectangle.x + drawArea.rectangle.width - textSize.x,
        drawArea.rectangle.y + drawArea.rectangle.height - textSize.y,
        textSize.x,
        textSize.y,
    };
    GuiLabel((Rectangle){
        labelRect.x * drawArea.scale,
        labelRect.y * drawArea.scale,
        labelRect.width * drawArea.scale,
        labelRect.height * drawArea.scale,
    }, s.c_str());
}

void AimReticle::drawAt(const DrawArea &drawArea) {
    drawHalfSizeRects(drawArea);
    drawSizeLabel(drawArea);
}

} // UI