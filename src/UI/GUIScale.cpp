//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "GUIScale.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace UI::GuiScale {

float guiScale = 1;

static RawStyle defaultStyle;

void init() {
    defaultStyle = {
        .textSize = GuiGetStyle(DEFAULT, TEXT_SIZE),
        .scrollBarWidth = {
            .def = GuiGetStyle(DEFAULT, SCROLLBAR_WIDTH),
            .listView = GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),
        }
    };
}

void apply() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)((float)defaultStyle.textSize * guiScale));
    GuiSetStyle(DEFAULT, SCROLLBAR_WIDTH, (int)((float)defaultStyle.scrollBarWidth.def * guiScale));
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, (int)((float)defaultStyle.scrollBarWidth.listView * guiScale));
    GuiSetIconScale(static_cast<int>(guiScale));
}

const RawStyle &getRawStyle() {
    return defaultStyle;
}

} // UI