//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef INTERACTIVITYWRAPPER_H
#define INTERACTIVITYWRAPPER_H

#include "IDrawable.h"

namespace UI {

class InteractivityWrapper : public IDrawable {
    IDrawable* drawable;
    bool interactable;
public:
    InteractivityWrapper(IDrawable* drawable, bool interactable);
    void drawAt(const DrawArea &drawArea) override;
};

} // UI

#endif //INTERACTIVITYWRAPPER_H
