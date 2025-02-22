//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "AimReticle.h"
#include "raygui.h"
#include "Label.h"

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
    const Label label = {
        .text = s.c_str(),
        .font = GetFontDefault(),
    };
    const Vector2 textSize = label.estimatedSize(drawRequest.scale());
    const Rectangle labelRect {
        drawRequest.rectangle.x + drawRequest.rectangle.width - textSize.x,
        drawRequest.rectangle.y + drawRequest.rectangle.height - textSize.y,
        textSize.x,
        textSize.y,
    };
    label.toDrawable()->drawAt(drawRequest.child("sizeLabel", labelRect));
}

void AimReticle::drawAt(const DrawRequest &drawRequest) {
    drawHalfSizeRects(drawRequest);
    drawSizeLabel(drawRequest);
}

} // UI