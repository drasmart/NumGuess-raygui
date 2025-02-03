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

void ScrollWrapper::drawAt(const DrawRequest &drawRequest) {
    Rectangle view;

    GuiScrollPanel({
            drawRequest.rectangle.x * drawRequest.scale(),
            drawRequest.rectangle.y * drawRequest.scale(),
            drawRequest.rectangle.width * drawRequest.scale(),
            drawRequest.rectangle.height * drawRequest.scale(),
        },
    title,
{
        drawRequest.rectangle.x * drawRequest.scale(),
        drawRequest.rectangle.y * drawRequest.scale(),
        size.x * drawRequest.scale(),
        size.y * drawRequest.scale(),
    },
    &offset,
    &view
    );

    BeginScissorMode(
        view.x,
        view.y,
        view.width,
        view.height);

    content->drawAt(drawRequest.child("scroll-boxed", {
        (view.x + offset.x) / drawRequest.scale(),
        (view.y + offset.y) / drawRequest.scale(),
        size.x,
        size.y,
    }));

    EndScissorMode();
}

} // UI