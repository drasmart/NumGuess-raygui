//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "GUIScale.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace UI::GuiScale {

float guiScale = 1;

static struct {
    int textSize;
    int scrollBarWidth;
} defaultStyle;

void init() {
    defaultStyle = {
        .textSize = GuiGetStyle(DEFAULT, TEXT_SIZE),
        .scrollBarWidth = GuiGetStyle(DEFAULT, SCROLLBAR_WIDTH),
    };
}

void apply() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, defaultStyle.textSize * guiScale);
    GuiSetStyle(DEFAULT, SCROLLBAR_WIDTH, defaultStyle.scrollBarWidth * guiScale);
    GuiSetIconScale(static_cast<int>(guiScale));
}

} // UI