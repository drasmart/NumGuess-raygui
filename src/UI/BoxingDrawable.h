//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef BOXINGDRAWABLE_H
#define BOXINGDRAWABLE_H

#include "IDrawable.h"

#include <memory>

namespace UI {

class BoxingDrawable : public IDrawable {
    std::unique_ptr<IDrawable> main;
    std::unique_ptr<IDrawable> nested;
public:
    BoxingDrawable(std::unique_ptr<IDrawable> &main, std::unique_ptr<IDrawable> &nested)
    : main(std::move(main)), nested(std::move(nested)) {}
    void drawAt(const DrawRequest &drawRequest) override {
        main->drawAt(drawRequest);
    }
};

} // UI

#endif //BOXINGDRAWABLE_H
