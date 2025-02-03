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

static void dumpIds(const DrawArea *drawArea, std::stringstream &ss) {
    if (drawArea->parent) {
        dumpIds(drawArea->parent, ss);
    }
    if (!drawArea->id) {
        return;
    }
    ss << '.';
    if (drawArea->id->index()) {
        ss << std::get<1>(*drawArea->id);
    } else {
        ss << std::get<0>(*drawArea->id);
    }
}

std::string DrawArea::buildFullID() const {
    std::stringstream ss;
    dumpIds(this, ss);
}

} // UI