//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "DrawArea.h"
#include <memory>

namespace UI {

struct IDrawable {
    virtual void drawAt(const DrawArea &drawArea) = 0;
    virtual ~IDrawable();

    std::unique_ptr<IDrawable> scrollable(const char *title, const Vector2 &size, Vector2 &offset);
    std::unique_ptr<IDrawable> interactable(bool interactable);
};

} // UI

#endif //IDRAWABLE_H
