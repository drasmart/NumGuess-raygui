//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef GUISCALE_H
#define GUISCALE_H

namespace UI::GuiScale {

extern float guiScale;

struct RawStyle {
    int textSize;
    struct {
        int def;
        int listView;
    } scrollBarWidth;
};

extern void init();
extern void apply();
extern const RawStyle &getRawStyle();

} // UI

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT   24 * UI::GuiScale::guiScale
#define RAYGUI_WINDOWBOX_CLOSEBUTTON_HEIGHT 18 * UI::GuiScale::guiScale
#define RAYGUI_LINE_MARGIN_TEXT             12 * UI::GuiScale::guiScale
#define RAYGUI_LINE_TEXT_PADDING             4 * UI::GuiScale::guiScale
#define RAYGUI_MESSAGEBOX_BUTTON_HEIGHT     24 * UI::GuiScale::guiScale
#define RAYGUI_MESSAGEBOX_BUTTON_PADDING    12 * UI::GuiScale::guiScale
#define RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT   24 * UI::GuiScale::guiScale
#define RAYGUI_TEXTINPUTBOX_BUTTON_PADDING  12 * UI::GuiScale::guiScale
#define RAYGUI_TEXTINPUTBOX_HEIGHT          26 * UI::GuiScale::guiScale
#define ICON_TEXT_PADDING                    4 * UI::GuiScale::guiScale
//#define RAYGUI_COLORBARALPHA_CHECKED_SIZE   10 * UI::GuiScale::guiScale
#define RAYGUI_GROUPBOX_LINE_THICK          (int)UI::GuiScale::guiScale
#define RAYGUI_PANEL_BORDER_WIDTH           (int)UI::GuiScale::guiScale

#endif //GUISCALE_H
