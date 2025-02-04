//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "IDrawable.h"

#include "AimReticle.h"
#include "FuncDrawable.h"

#include "raygui.h"

namespace UI {

IDrawable::~IDrawable() = default;

std::unique_ptr<IDrawable> IDrawable::scrollable(const char *title, const Vector2 &size, Vector2 &offset) {
    return std::make_unique<FuncDrawable>([title, this, size, &offset](const DrawRequest &drawRequest) {
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

        this->drawAt(drawRequest.child("scroll-boxed", {
            (view.x + offset.x) / drawRequest.scale(),
            (view.y + offset.y) / drawRequest.scale(),
            size.x,
            size.y,
        }));

        EndScissorMode();
    });
}

std::unique_ptr<IDrawable> IDrawable::interactable(bool interactable) {
    return std::make_unique<FuncDrawable>([this, interactable](const DrawRequest &drawRequest) {
        const bool globalInteractable = !GuiIsLocked();
        if (globalInteractable != interactable) {
            if (interactable) {
                GuiUnlock();
            } else {
                GuiLock();
            }
        }
        this->drawAt(drawRequest);
        if (globalInteractable != interactable) {
            if (globalInteractable) {
                GuiUnlock();
            } else {
                GuiLock();
            }
        }
    });
}

std::unique_ptr<IDrawable> IDrawable::focusable(bool enabled) {
    return std::make_unique<FuncDrawable>([this, enabled](const DrawRequest &drawRequest) {
        const bool focused = drawRequest.context->focusManager.checkFocus(
            drawRequest.toFocusable(), enabled);
        this->interactable(enabled)->drawAt(drawRequest);
        if (focused) {
            AimReticle().drawAt(drawRequest.child("focus-reticle"));
        }
    });
}

} // UI
