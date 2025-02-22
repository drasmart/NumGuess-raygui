//
// Created by Maksym Kucherov on 22-Feb-25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <optional>
#include <string>

namespace Game {

    typedef int NumType; // int to match ValueBox

    struct GuessSession {
        NumType targetNumber = 0;
        NumType maxValue = 100;
        std::vector<NumType> guesses;
        struct {
            std::optional<NumType> low;
            std::optional<NumType> high;
        } misses;

        [[nodiscard]] bool started() const {
          return targetNumber > 0;
        }
        [[nodiscard]] bool completed() const {
          return !guesses.empty() && guesses.back() == targetNumber;
        }
        int addGuess(NumType number) {
            guesses.push_back(number);
            if (number < targetNumber && misses.low.value_or(0) < number) {
                misses.low = number;
            }
            if (number > targetNumber && number < misses.high.value_or(maxValue + 1)) {
                misses.high = number;
            }
            return number - targetNumber;
        }
    };

    struct PlaySession {
        std::string playerName;
        std::vector<GuessSession> sessions;
    };

    enum class ExpectedInput {
        Name,
        Guess,
        NewGame,
        MaxValue,
    };

    struct Engine {
        PlaySession data;

        [[nodiscard]] ExpectedInput nextInput() const;
        void setName(const std::string& playerName);
        int makeGuess(NumType number);
        void startNewGame();
        void setMaxValue(NumType maxValue);
    };
}

#endif //ENGINE_H
