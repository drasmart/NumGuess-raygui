//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef AIMRETICLE_H
#define AIMRETICLE_H

#include "IDrawable.h"

namespace UI {

struct AimReticle : IDrawable {
    void drawAt(const DrawRequest &drawRequest) override;
};

} // UI

#endif //AIMRETICLE_H
