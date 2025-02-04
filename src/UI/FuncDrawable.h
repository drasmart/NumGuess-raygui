//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef FUNCDRAWABLE_H
#define FUNCDRAWABLE_H

#include "IDrawable.h"

#include <functional>

namespace UI {

class FuncDrawable : public IDrawable {
    const std::function<void(const DrawRequest &drawRequest)> func;
public:
    explicit FuncDrawable(const std::function<void(const DrawRequest &drawRequest)> &func);
    void drawAt(const DrawRequest &drawRequest) override;
};

} // UI

#endif //FUNCDRAWABLE_H
