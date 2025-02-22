//
// Created by Maksym Kucherov on 22-Feb-25.
//

#include "GuessRangeBar.h"
#include "FuncDrawable.h"
#include "raylib.h"
#include "Label.h"
#include <sstream>

namespace Game {

    using namespace UI;

    static const float barHeight = 7;

    std::unique_ptr<IDrawable> GuessRangeBar::toDrawable() const {
        struct {
            NumType maxValue = 0;
            std::optional<NumType> targetNum;
            std::optional<NumType> lowMiss;
            std::optional<NumType> highMiss;
            size_t attempts = 0;
        } const summary {
            session.maxValue,
            session.completed() ? std::optional(session.targetNumber) : std::nullopt,
            session.misses.low,
            session.misses.high,
            session.guesses.size(),
        };
        return std::make_unique<FuncDrawable>([summary](const DrawRequest &drawRequest) {
            const Rectangle barRect = [](Rectangle baseRect, const float h) {
                baseRect.y += baseRect.height / 2 - h / 2;
                baseRect.height = h;
                return baseRect;
            }(drawRequest.scaledRectangle(), barHeight * drawRequest.scale());
            const Rectangle rect = drawRequest.scaledRectangle();
            {
                const Rectangle rect = drawRequest.scaledRectangle();
                DrawRectangleLines(
                    (int)rect.x,
                    (int)rect.y,
                    (int)rect.width,
                    (int)rect.height,
                    Color{ 255, 0, 255, 255 });
            }
            {
                DrawRectangle(
                    (int)barRect.x,
                    (int)barRect.y,
                    (int)barRect.width,
                    (int)barRect.height,
                    summary.targetNum.has_value()
                    ? Color{ 0, 255, 0, 255 }
                    : Color{ 0, 96, 255, 255 });
            }
            const Font f = GetFontDefault();
            {
                const Label l { "1", f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("minValue", r));
            }
            {
                auto const mx = (std::stringstream() << summary.maxValue).str();
                const Label l { mx.c_str(), f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.x += r.width - s.x;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("maxValue", r));
            }
            {
                std::stringstream ss;
                ss << "( ";
                if (summary.lowMiss.has_value()) {
                    ss << summary.lowMiss.value();
                    Rectangle rect = barRect;
                    const float w = (summary.lowMiss.value() - 1) / (summary.maxValue - 1.0f) * rect.width;
                    rect.width = w;
                    DrawRectangle(
                        (int)rect.x,
                        (int)rect.y,
                        (int)rect.width,
                        (int)rect.height,
                        Color{ 220, 128, 128, 255 });
                } else {
                    ss << '?';
                }
                ss << " )";
                auto const t = ss.str();
                const Label l { t.c_str(), f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.y += r.height - s.y;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("lowMiss", r));
            }
            {
                std::stringstream ss;
                ss << "( ";
                if (summary.highMiss.has_value()) {
                    ss << summary.highMiss.value();
                    Rectangle rect = barRect;
                    const float w = (summary.maxValue - summary.highMiss.value()) / (summary.maxValue - 1.0f) * rect.width;
                    rect.x += rect.width - w;
                    rect.width = w;
                    DrawRectangle(
                        (int)rect.x,
                        (int)rect.y,
                        (int)rect.width,
                        (int)rect.height,
                        Color{ 220, 128, 128, 255 });
                } else {
                    ss << '?';
                }
                ss << " )";
                auto const t = ss.str();
                const Label l { t.c_str(), f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.x += r.width - s.x;
                r.y += r.height - s.y;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("highMiss", r));
            }
            {
                std::stringstream ss;
                if (summary.targetNum.has_value()) {
                    ss << summary.targetNum.value();
                } else {
                    ss << '?';
                }
                auto const t = ss.str();
                const Label l { t.c_str(), f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.x += (r.width - s.x) / 2;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("target", r));
            }
            {
                auto const t = (std::stringstream() << summary.attempts << " attempts").str();
                const Label l { t.c_str(), f };
                const Vector2 s = l.estimatedSize(drawRequest.scale());
                Rectangle r = drawRequest.rectangle;
                r.x += (r.width - s.x) / 2;
                r.y += r.height - s.y;
                r.width = s.x;
                r.height = s.y;
                l.toDrawable()->drawAt(drawRequest.child("attempts", r));
            }
        });
    }

    float GuessRangeBar::getHeight(const float scale) {
        return barHeight + 2 * Label {
            "1",
            GetFontDefault(),
        }.estimatedSize(scale).y;
    }

} // Game
