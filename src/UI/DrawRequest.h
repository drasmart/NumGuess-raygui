//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"
#include <string>
#include <variant>

namespace UI {

struct Context;

typedef std::variant<std::string, int> DrawRequestIdFragment;

struct DrawRequest {
    const Rectangle rectangle;
    const DrawRequestIdFragment id;
    const DrawRequest * const parent;
    Context * const context;

    [[nodiscard]]
    DrawRequest child(
        const DrawRequestIdFragment &key, Rectangle rect) const;

    [[nodiscard]]
    DrawRequest child(const DrawRequestIdFragment &key) const {
        return child(key, rectangle);
    }

    void dumpIds(std::ostream &ss) const;
    [[nodiscard]]
    std::string fullId() const;

    [[nodiscard]]
    float scale() const;
};

} // UI

#endif //SCALEDRECTANGLE_H
