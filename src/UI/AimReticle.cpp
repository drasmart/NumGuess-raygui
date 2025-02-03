//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "AimReticle.h"
#include "raygui.h"

#include <sstream>

namespace UI {

static void drawHalfSizeRects(const DrawRequest &drawRequest) {
    DrawRectangle(
        drawRequest.rectangle.x * drawRequest.scale(),
        drawRequest.rectangle.y * drawRequest.scale(),
        drawRequest.rectangle.width / 2 * drawRequest.scale(),
        drawRequest.rectangle.height / 2 * drawRequest.scale(),
        Color(255, 0, 0, 64));
    DrawRectangle(
        (drawRequest.rectangle.x + drawRequest.rectangle.width / 2) * drawRequest.scale(),
        (drawRequest.rectangle.y + drawRequest.rectangle.height / 2) * drawRequest.scale(),
        drawRequest.rectangle.width / 2 * drawRequest.scale(),
        drawRequest.rectangle.height / 2 * drawRequest.scale(),
        Color(0, 0, 255, 64));
}

static void drawSizeLabel(const DrawRequest &drawRequest) {
    std::stringstream ss;
    ss
    << "( "
    << drawRequest.rectangle.width
    << " , "
    << drawRequest.rectangle.height
    << " ) @ "
    << drawRequest.scale()
    << "x";
    const std::string s = ss.str();
    const Font font = GetFontDefault();
    const Vector2 textSizeRaw = MeasureTextEx(
        font,
        s.c_str(),
        (float)GuiGetStyle(DEFAULT, TEXT_SIZE),
        (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
    const float padding = (int)drawRequest.scale() + 1;
    const Vector2 textSize {
        textSizeRaw.x / drawRequest.scale() + padding,
        textSizeRaw.y / drawRequest.scale() + padding,
    };
    const Rectangle labelRect {
        drawRequest.rectangle.x + drawRequest.rectangle.width - textSize.x,
        drawRequest.rectangle.y + drawRequest.rectangle.height - textSize.y,
        textSize.x,
        textSize.y,
    };
    GuiLabel((Rectangle){
        labelRect.x * drawRequest.scale(),
        labelRect.y * drawRequest.scale(),
        labelRect.width * drawRequest.scale(),
        labelRect.height * drawRequest.scale(),
    }, s.c_str());
}

void AimReticle::drawAt(const DrawRequest &drawRequest) {
    drawHalfSizeRects(drawRequest);
    drawSizeLabel(drawRequest);
}

} // UI