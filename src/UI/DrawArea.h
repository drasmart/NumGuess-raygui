//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"
#include <optional>
#include <string>
#include <variant>

namespace UI {

typedef std::variant<std::string, int> DrawAreaIdFragment;

struct DrawArea {
    Rectangle rectangle;
    float scale = 1;
    std::optional<Rectangle> clipArea;
    std::optional<DrawAreaIdFragment> id;
    const DrawArea *parent = nullptr;

    DrawArea child(
        const DrawAreaIdFragment &key,
        Rectangle rect,
        const std::optional<Rectangle> &newClipArea = std::nullopt) const;

    void dumpIds(std::ostream &ss) const;
};

} // UI

#endif //SCALEDRECTANGLE_H
