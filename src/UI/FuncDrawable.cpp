//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "FuncDrawable.h"

namespace UI {

FuncDrawable::FuncDrawable(const std::function<void(const DrawRequest &drawRequest)> &func): func(func) {}

void FuncDrawable::drawAt(const DrawRequest &drawRequest) {
    func(drawRequest);
}

} // UI