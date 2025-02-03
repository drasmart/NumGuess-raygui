//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"
#include "raygui.h"

#include "AimReticle.h"

namespace UI {

void Root::drawScrollPanel(const DrawArea &drawArea) {

    demoBox2.scrollable("SCROLL AREA",
        {
            drawArea.rectangle.width,
            drawArea.rectangle.height,
        },
        scroll)
    ->drawAt( drawArea.child("scroll-panel", {
        drawArea.rectangle.x + drawArea.rectangle.width / 2,
        drawArea.rectangle.y,
        drawArea.rectangle.width / 2,
        drawArea.rectangle.height,
    }));
}

void Root::drawScrollPanel2(const DrawArea &drawArea) {

    AimReticle().scrollable("SCROLL AREA 2",
        {
            drawArea.rectangle.width / 4,
            drawArea.rectangle.height,
        },
        scroll2)
    ->interactable(false)
    ->drawAt( drawArea.child("scroll-panel-2", {
        drawArea.rectangle.x + drawArea.rectangle.width * 5 / 8,
        drawArea.rectangle.y + drawArea.rectangle.height / 4,
        drawArea.rectangle.width / 4,
        drawArea.rectangle.height / 2,
    }));
}

void Root::drawAt(const DrawArea &drawArea) {
    drawScrollPanel(drawArea);
    drawScrollPanel2(drawArea);
    demoBox1.drawAt(drawArea);
}

} // UI