//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "DrawArea.h"

#include <sstream>

namespace UI {


DrawArea DrawArea::child(
    const DrawAreaIdFragment &key,
    Rectangle rect,
    const std::optional<Rectangle> &newClipArea) const
{
    return DrawArea {
        rect,
        scale,
        newClipArea ? newClipArea : clipArea,
        key,
        this,
    };
}

void DrawArea::dumpIds(std::ostream &ss) const {
    if (parent) {
        parent->dumpIds(ss);
        ss << '.';
    }
    if (!id) {
        return;
    }
    if (id->index()) {
        ss << std::get<1>(*id);
    } else {
        ss << std::get<0>(*id);
    }
}

} // UI