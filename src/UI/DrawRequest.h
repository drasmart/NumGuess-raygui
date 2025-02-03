//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"
#include <string>
#include <variant>

#include "Context.h"

namespace UI {

typedef std::variant<std::string, int> DrawRequestIdFragment;

struct DrawRequest {
    const Rectangle rectangle;
    const DrawRequestIdFragment id;
    const DrawRequest * const parent;
    Context * const context;

    DrawRequest child(
        const DrawRequestIdFragment &key,
        Rectangle rect) const;

    void dumpIds(std::ostream &ss) const;
    float scale() const { return context->scale; }
};

} // UI

#endif //SCALEDRECTANGLE_H
