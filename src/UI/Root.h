//
// Created by Maksym Kucherov on 02-Feb-25.
//

#ifndef ROOT_H
#define ROOT_H

#include "IDrawable.h"
#include "DemoButtonMsgBox.h"

namespace UI {

struct Root : IDrawable {
    DemoButtonMsgBox demoBox1;
    DemoButtonMsgBox demoBox2;
    Vector2 scroll { 0, 0 };
    Vector2 scroll2 { -50, -180 };

    void drawAt(const DrawArea &drawArea) override;
private:
    void drawScrollPanel(const DrawArea &drawArea);
    void drawScrollPanel2(const DrawArea &drawArea);
};

} // UI

#endif //ROOT_H
