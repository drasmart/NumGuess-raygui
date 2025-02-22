//
// Created by Maksym Kucherov on 22-Feb-25.
//

#include "DirectionalBox.h"

#include "FuncDrawable.h"
#include "BoxingDrawable.h"

#include "raygui.h"

namespace UI {

    std::unique_ptr<IDrawable> DirectionalBox::toDrawable() const {
        return std::make_unique<FuncDrawable>([clone = *this](const DrawRequest &drawRequest){
            std::vector<DrawRequestIdFragment> keys;
            keys.reserve(clone.count);
            for (size_t i = 0; i < clone.count; i++) {
                keys.push_back(clone.keys(i));
            }
            float minFitWidth;
            if (clone.direction.x != 0) {
                minFitWidth = (
                (drawRequest.rectangle.width
                    - (float)(clone.count + 1) * clone.insets.x)
                    / (float)clone.count
                );
            } else {
                minFitWidth = drawRequest.rectangle.width - 2 * clone.insets.x;
            }
            Vector2 maxSize = { 0, 0 };
            Vector2 fullSize = {
                (clone.direction.x * ((float)clone.count - 1) + 2) * clone.insets.x,
                (clone.direction.y * ((float)clone.count - 1) + 2) * clone.insets.y,
            };
            for (const auto &key : keys) {
                const Vector2 nextSize = clone.preferredSizes(key, minFitWidth, drawRequest.rectangle.width);
                if (maxSize.x < nextSize.x) {
                    maxSize.x = nextSize.x;
                }
                if (maxSize.y < nextSize.y) {
                    maxSize.y = nextSize.y;
                }
                fullSize.x += clone.direction.x * nextSize.x;
                fullSize.y += clone.direction.y * nextSize.y;
            }
            fullSize.x += (1 - clone.direction.x) * maxSize.x;
            fullSize.y += (1 - clone.direction.y) * maxSize.y;
            FuncDrawable([&clone, &keys, &maxSize](const DrawRequest &drawRequest2) {
                Rectangle rect = {
                    drawRequest2.rectangle.x + clone.insets.x,
                    drawRequest2.rectangle.y + clone.insets.y,
                    maxSize.x,
                    maxSize.y,
                };
                for (size_t i = 0; i < clone.count; i++) {
                    clone.drawers(keys[i], drawRequest2.child(keys[i], rect));
                    rect.x += clone.direction.x * (clone.insets.x + maxSize.x);
                    rect.y += clone.direction.y * (clone.insets.y + maxSize.y);
                }
            }).scrollable(clone.title, fullSize, clone.offset)->drawAt(drawRequest);
        });
    }

} // UI
