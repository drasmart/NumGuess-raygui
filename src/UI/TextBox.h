//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "IDrawable.h"

#include <memory>
#include <functional>

namespace UI {

struct TextBox {
    char * const textBuffer;
    const int textSize;
    const std::function<void(const DrawRequest &)> onEnter;
    const bool enabled = true;

    [[nodiscard]]
    std::unique_ptr<IDrawable> toDrawable() const;
};

} // UI

#endif //TEXTBOX_H
