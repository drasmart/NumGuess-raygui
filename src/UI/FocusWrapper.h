//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef FOCUSWRAPPER_H
#define FOCUSWRAPPER_H

#include "IDrawable.h"

namespace UI {

class FocusWrapper : public IDrawable {
    IDrawable * const content;
    const bool focusable;
public:
    FocusWrapper(IDrawable * content, bool focusable);
    void drawAt(const DrawRequest &drawRequest) override;
};

} // UI

#endif //FOCUSWRAPPER_H
