//
// Created by Maksym Kucherov on 03-Feb-25.
//

#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include "raylib.h"

#include <string>
#include <vector>
#include <optional>

namespace UI {

struct Focusable {
    std::string id;
    Rectangle rect;
};

class FocusManager {
    std::optional<std::string> selected;
    std::vector<Focusable> focusables;
    bool didMoveFocus = false;

public:
    void claimFocus(const Focusable &request);
    void dropFocus(const Focusable &request);
    [[nodiscard]]
    bool checkFocus(const Focusable &request, bool focusable);
    void clearCache();
    void moveNext() { move(+1); }
    void movePrev() { move(-1); }
    [[nodiscard]]
    bool focusMoved() const { return didMoveFocus; }

private:
    void move(int dx);
};

} // UI

#endif //FOCUSMANAGER_H
