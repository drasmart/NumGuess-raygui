//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "IDrawable.h"

#include <memory>
#include <functional>

namespace UI {

    struct Button {
        const char * const title = nullptr;
        const std::function<void()> callback;
        const bool enabled = true;

        [[nodiscard]]
        std::unique_ptr<IDrawable> toDrawable() const;
    };

} // UI

#endif //BUTTON_H
