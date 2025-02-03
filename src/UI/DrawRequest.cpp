//
// Created by Maksym Kucherov on 03-Feb-25.
//

#include "DrawRequest.h"

#include <sstream>

namespace UI {


DrawRequest DrawRequest::child(
    const DrawRequestIdFragment &key,
    Rectangle rect) const
{
    return DrawRequest {
        rect,
        key,
        this,
        context,
    };
}

void DrawRequest::dumpIds(std::ostream &ss) const {
    if (parent) {
        parent->dumpIds(ss);
        ss << '.';
    }
    if (id.index()) {
        ss << std::get<1>(id);
    } else {
        ss << std::get<0>(id);
    }
}

} // UI