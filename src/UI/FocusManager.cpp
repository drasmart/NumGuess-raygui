//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "FocusManager.h"

#include <execution>

namespace UI {

void FocusManager::claimFocus(const Focusable &request) {
    if (selected && *selected == request.id) {
        return;
    }
    selected = request.id;
    const auto it = std::find_if(
        std::execution::seq, focusables.begin(), focusables.end(),
        [&](auto&& x) { return x.id == *selected; });
    didMoveFocus = true;
    if (it == focusables.end()) {
        focusables.push_back(request);
    }
}

void FocusManager::dropFocus(const Focusable &request)
{
    if (selected && *selected == request.id) {
        selected = std::nullopt;
        didMoveFocus = true;
    }
}

bool FocusManager::checkFocus(const Focusable &request, bool focusable)
{
    focusables.push_back(request);
    if (!focusable) {
        dropFocus(request);
        return false;
    }
    if (selected) {
        return *selected == request.id;
    }
    selected = request.id;
    didMoveFocus = true;
    return true;
}

void FocusManager::clearCache()
{
    focusables.clear();
    didMoveFocus = false;
}

void FocusManager::move(const int dx) {
    if (focusables.empty()) {
        return;
    }
    didMoveFocus = true;
    if (!selected) {
        selected = focusables[0].id;
        return;
    }
    auto it = std::find_if(
        std::execution::seq, focusables.begin(), focusables.end(),
        [&](auto&& x) { return x.id == *selected; });
    if (it == focusables.end()) {
        selected = focusables[0].id;
        return;
    }
    if (dx < 0) {
        selected = (
            (it == focusables.begin())
            ? focusables.rbegin()->id
            : (--it)->id);
        return;
    }
    if (++it == focusables.end()) {
        it = focusables.begin();
    }
    selected = it->id;
}

} // UI