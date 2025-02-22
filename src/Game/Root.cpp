//
// Created by Maksym Kucherov on 02-Feb-25.
//

#include "Root.h"

#include <iostream>
#include <Label.h>
#include <sstream>

#include "raygui.h"

#include "AimReticle.h"
#include "Button.h"
#include "GUIScale.h"
#include "TextBox.h"
#include "ValueBox.h"
#include "DirectionalBox.h"
#include "GuessRangeBar.h"

namespace Game {

    using namespace UI;

    static constexpr float SideSplitFactor = 0.7f;
    static constexpr float GuessRangeBarFrameThickness = 1;
    static constexpr float GuessRangeBarFramePadding = 2;
    static constexpr float MainFrameInset = 4;

    static void drawHistoryScrollPanel(Root &root, const DrawRequest &drawRequest) {

        DirectionalBox {
            .title = "Last Game Results",
            .direction = { 0, 1 },
            .offset = root.historyScroll,
            .insets = { MainFrameInset, MainFrameInset },
            .alignment = 0.5f,
            .count = root.engine.data.sessions.size(),
            .keys = [&root](size_t x) {
                return (int)(root.engine.data.sessions.size() - x - 1);
            },
            .preferredSizes = [](const DrawRequestIdFragment &idFrag, float mn, const DrawRequest &drawRequest2) {
                return Vector2 {
                    mn - (float)GuiScale::getRawStyle().scrollBarWidth.listView - 1,
                    GuessRangeBar::getHeight(drawRequest2.scale())
                    + 2 * (GuessRangeBarFrameThickness + GuessRangeBarFramePadding),
                };
            },
            .drawers = [&ss = root.engine.data.sessions](const DrawRequestIdFragment &idFrag, const DrawRequest &drawRequest2) {
                GuessRangeBar { ss[std::get<1>(idFrag)] }
                .toDrawable()
                ->padding(GuessRangeBarFramePadding)
                ->filled({ 255, 255, 255, 255 })
                ->padding(GuessRangeBarFrameThickness)
                ->filled({ 127, 127, 127, 255 })
                ->drawAt(drawRequest2);
            },
        }
        .toDrawable()
        ->drawAt( drawRequest.child("history-panel", {
            drawRequest.rectangle.x + drawRequest.rectangle.width * SideSplitFactor,
            drawRequest.rectangle.y,
            drawRequest.rectangle.width * (1 - SideSplitFactor),
            drawRequest.rectangle.height,
        }));
    }

    static float getInputPanelHeight(const DrawRequest &drawRequest) {
        return RAYGUI_MESSAGEBOX_BUTTON_HEIGHT / GuiScale::guiScale + 2 * MainFrameInset;
    }

    static void drawTextScrollPanel(Root &root, const DrawRequest &drawRequest) {

        DirectionalBox {
            .title = "Chat log",
            .direction = { 0, 1 },
            .offset = root.textScroll,
            .insets = { MainFrameInset, MainFrameInset },
            .alignment = 0.5f,
            .count = root.chatLog.size() + 1,
            .keys = [](size_t x) {
                return (int)(x);
            },
            .preferredSizes = [](const DrawRequestIdFragment &idFrag, float mn, const DrawRequest &drawRequest2) {
                return Vector2 {
                    mn - (float)GuiScale::getRawStyle().scrollBarWidth.listView - 1,
                    Label { "dbqp", GetFontDefault() }.estimatedSize(drawRequest2.scale()).y,
                };
            },
            .drawers = [&root](const DrawRequestIdFragment &idFrag, const DrawRequest &btnReq) {
                const size_t x = std::get<1>(idFrag);
                const char *msg;
                if (x < root.chatLog.size()) {
                    msg = root.chatLog[x].c_str();
                } else {
                    switch (root.engine.nextInput()) {
                        case ExpectedInput::Name:
                            msg = "Kindly name yourself...";
                            break;
                        case ExpectedInput::Guess:
                            msg = "Make your guess...";
                            break;
                        case ExpectedInput::MaxValue:
                            msg = "Pick your ceiling...";
                            break;
                        case ExpectedInput::NewGame:
                            msg = "Start again?...";
                            break;
                        default:
                            throw std::logic_error("This should be impossible.");
                    }
                }
                Label { msg, GetFontDefault() }.toDrawable()->drawAt(btnReq);
            },
        }
        .toDrawable()
        ->drawAt( drawRequest.child("chat-panel", {
            drawRequest.rectangle.x,
            drawRequest.rectangle.y,
            drawRequest.rectangle.width * SideSplitFactor,
            drawRequest.rectangle.height - getInputPanelHeight(drawRequest),
        }));
    }

    static void drawInputPanel(Root &root, const DrawRequest &drawRequest) {
        Rectangle rectangle = drawRequest.rectangle;
        rectangle.width *= SideSplitFactor;
        const float h = getInputPanelHeight(drawRequest);
        rectangle.y = rectangle.height - h;
        rectangle.height = h;

        const ExpectedInput input = root.engine.nextInput();
        switch (input) {
            case ExpectedInput::Name: {
                TextBox {
                    .textBuffer = root.nameBuf,
                    .textSize = sizeof(root.nameBuf),
                    .onEnter = [&root](const DrawRequest &senderDrawRequest) {
                        std::cout << "TEXT entered! -- " << root.nameBuf << std::endl;
                        const std::string name = root.nameBuf;
                        if (name.empty()) {
                            return;
                        }
                        root.say("Nice to meet you, " + name + ".");
                        root.engine.setName(name);
                        senderDrawRequest.dropFocus();
                    },
                }.toDrawable()
                ->padding(MainFrameInset)
                ->drawAt(drawRequest.child("nameBox", rectangle));
                break;
            }
            case ExpectedInput::NewGame: {
                Button {
                    "Start New Game",
                    [&root](const DrawRequest &senderDrawRequest) {
                        std::cout << "BTN clicked!" << std::endl;
                        root.say("Challenge accepted!");
                        root.num = root.engine.data.sessions.back().maxValue;
                        root.engine.startNewGame();
                        senderDrawRequest.dropFocus();
                    },
                }.toDrawable()
                ->padding(MainFrameInset)
                ->drawAt(drawRequest.child("newGameBtn", rectangle));
                break;
            }
            case ExpectedInput::MaxValue:
            case ExpectedInput::Guess: {
                int &maxValue = root.engine.data.sessions.back().maxValue;
                ValueBox {
                    "",
                    input == ExpectedInput::Guess
                    ? &root.num
                    : &maxValue,
                    0,
                    input == ExpectedInput::Guess
                    ? maxValue
                    : INT_MAX,
                    [&root, input, &maxValue](const DrawRequest &senderDrawRequest) {
                        std::cout
                        << "ValueBox ENTER! >> "
                        << (input == ExpectedInput::Guess
                            ? root.num
                            : maxValue)
                        << std::endl;

                        if (!root.num) {
                            return;
                        }
                        if (input == ExpectedInput::MaxValue) {
                            root.say((std::stringstream() << "Hmm... a number between 1 and " << maxValue << "... Ok!").str());
                            root.engine.setMaxValue(maxValue);
                        } else {
                            std::stringstream ss;
                            ss << root.num << " -- ";
                            const int missSign = root.engine.makeGuess(root.num);
                            if (missSign < 0) {
                                ss << "Too low!";
                            } else if (missSign > 0) {
                                ss << "Too high!";
                            } else {
                                ss << "Correct!";
                            }
                            root.say(ss.str());
                            root.num = 0;
                        }
                        senderDrawRequest.dropFocus();
                    },
                }.toDrawable()
                ->padding(MainFrameInset)
                ->drawAt(drawRequest.child("numInputBox", rectangle));
                break;
            }
        }

    }

    void Root::drawAt(const DrawRequest &drawRequest) {
        drawInputPanel(*this, drawRequest);
        drawTextScrollPanel(*this, drawRequest);
        drawHistoryScrollPanel(*this, drawRequest);
    }

} // UI