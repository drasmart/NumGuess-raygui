//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "InteractivityWrapper.h"

#include "raygui.h"

namespace UI {

InteractivityWrapper::InteractivityWrapper(IDrawable* drawable, bool interactable)
    : drawable(drawable), interactable(interactable) {}

void InteractivityWrapper::drawAt(const DrawArea &drawArea) {
    const bool globalInteractable = !GuiIsLocked();
    if (globalInteractable != interactable) {
        if (interactable) {
            GuiUnlock();
        } else {
            GuiLock();
        }
    }
    drawable->drawAt(drawArea.child("x", drawArea.rectangle));
    if (globalInteractable != interactable) {
        if (globalInteractable) {
            GuiUnlock();
        } else {
            GuiLock();
        }
    }
}

} // UI