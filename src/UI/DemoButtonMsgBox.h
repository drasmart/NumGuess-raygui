//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef DEMOBUTTONMSGBOX_H
#define DEMOBUTTONMSGBOX_H

#include "IDrawable.h"

namespace UI {

struct  DemoButtonMsgBox : IDrawable {
    bool showMessageBox = false;
    void drawAt(const DrawArea &drawArea) override;
};

} // UI

#endif //DEMOBUTTONMSGBOX_H
