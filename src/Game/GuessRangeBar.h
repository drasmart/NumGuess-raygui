//
// Created by Maksym Kucherov on 22-Feb-25.
//

#ifndef GUESSRANGEBAR_H
#define GUESSRANGEBAR_H

#include "IDrawable.h"
#include "Engine.h"

#include <memory>
#include <functional>

namespace Game {

    struct GuessRangeBar {
        const GuessSession &session;

        [[nodiscard]]
        std::unique_ptr<UI::IDrawable> toDrawable() const;
        [[nodiscard]]
        static float getHeight(float scale);
    };

} // Game

#endif //GUESSRANGEBAR_H
