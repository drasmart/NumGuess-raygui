//
// Created by Maksym Kucherov on 22-Feb-25.
//

#include "Engine.h"
#include <random>

namespace Game {
    ExpectedInput Engine::nextInput() const {
        if (data.playerName.empty() || data.sessions.empty()) {
            return ExpectedInput::Name;
        }
        const GuessSession &lastSession = data.sessions.back();
        if (lastSession.completed()) {
            return ExpectedInput::NewGame;
        }
        if (!lastSession.started()) {
            return ExpectedInput::MaxValue;
        }
        return ExpectedInput::Guess;
    }

    void Engine::setName(const std::string& playerName) {
        data.playerName = playerName;
        if (!data.sessions.empty()) {
            return;
        }
        startNewGame();
        setMaxValue(data.sessions.back().maxValue);
    }

    void Engine::makeGuess(const NumType number) {
        data.sessions.back().addGuess(number);
    }

    void Engine::startNewGame() {
        data.sessions.emplace_back();
    }

    void Engine::setMaxValue(const NumType maxValue) {
        data.sessions.back().maxValue = maxValue;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<NumType> dist(1, maxValue);
        data.sessions.back().targetNumber = dist(mt);
    }
}
