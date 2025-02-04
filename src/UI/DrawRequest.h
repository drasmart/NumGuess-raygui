//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef SCALEDRECTANGLE_H
#define SCALEDRECTANGLE_H

#include "raylib.h"

#include "Context.h"

#include <string>
#include <variant>

namespace UI {

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

    [[nodiscard]]
    Focusable toFocusable() const { return { fullId(), rectangle }; }

    [[nodiscard]]
    bool checkFocus(bool enabled) const { return context->focusManager.checkFocus(toFocusable(), enabled); }
    void claimFocus() const { context->focusManager.claimFocus(toFocusable()); }
    void dropFocus() const { context->focusManager.dropFocus(toFocusable()); }

    [[nodiscard]]
    Rectangle scaledRectangle() const {
        const float k = scale();
        return {
            rectangle.x * k,
            rectangle.y * k,
            rectangle.width * k,
            rectangle.height * k,
        };
    }
};

} // UI

#endif //SCALEDRECTANGLE_H
