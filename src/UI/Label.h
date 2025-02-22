//
// Created by Maksym Kucherov on 22-Feb-25.
//

#ifndef LABEL_H
#define LABEL_H

#include "IDrawable.h"

#include <memory>
#include <functional>

namespace UI {

    struct Label {
        const char * const text;
        const Font font;

        [[nodiscard]]
        std::unique_ptr<IDrawable> toDrawable() const;
        [[nodiscard]]
        Vector2 estimatedSize(float scale) const;
    };

} // UI

#endif //LABEL_H
