//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef SCROLLWRAPPER_H
#define SCROLLWRAPPER_H

#include "IDrawable.h"

namespace UI {

class ScrollWrapper : public IDrawable {
    IDrawable *content;
    const Vector2 &size;
    Vector2 &offset;
    const char *title;

public:
    ScrollWrapper(const char *title, IDrawable *content, const Vector2 &size, Vector2 &offset);

    void drawAt(const DrawArea &drawArea) override;
};

} // UI

#endif //SCROLLWRAPPER_H
