//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "ScrollWrapper.h"

#include "raygui.h"

namespace UI {

ScrollWrapper::ScrollWrapper(const char *title, IDrawable *content, const Vector2 &size, Vector2 &offset):
    title(title),
    content(content),
    size(size),
    offset(offset)
    {}

void ScrollWrapper::drawAt(const DrawArea &drawArea) {
    Rectangle view;

    GuiScrollPanel({
            drawArea.rectangle.x * drawArea.scale,
            drawArea.rectangle.y * drawArea.scale,
            drawArea.rectangle.width * drawArea.scale,
            drawArea.rectangle.height * drawArea.scale,
        },
    title,
{
        drawArea.rectangle.x * drawArea.scale,
        drawArea.rectangle.y * drawArea.scale,
        size.x * drawArea.scale,
        size.y * drawArea.scale,
    },
    &offset,
    &view
    );

    BeginScissorMode(
        view.x,
        view.y,
        view.width,
        view.height);

    content->drawAt(drawArea.child("scroll-boxed", {
        (view.x + offset.x) / drawArea.scale,
        (view.y + offset.y) / drawArea.scale,
        size.x,
        size.y,
    }));

    EndScissorMode();
}

} // UI