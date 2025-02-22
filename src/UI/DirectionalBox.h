//
// Created by Maksym Kucherov on 22-Feb-25.
//

#ifndef DIRECTIONALBOX_H
#define DIRECTIONALBOX_H

#include "IDrawable.h"

#include <memory>
#include <functional>

namespace UI {

    struct DirectionalBox {
        const char * const title;
        const Vector2 direction;
        Vector2 &offset;
        const Vector2 insets;
        const float alignment;
        const size_t count;
        const std::function<DrawRequestIdFragment(size_t)> keys;
        const std::function<Vector2(const DrawRequestIdFragment &, float, const DrawRequest &)> preferredSizes;
        const std::function<void(const DrawRequestIdFragment &, const DrawRequest &)> drawers;

        [[nodiscard]]
        std::unique_ptr<IDrawable> toDrawable() const;
    };

} // UI

#endif //DIRECTIONALBOX_H
