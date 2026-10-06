//
// Created by JGrater on 05/10/2026.
//

#include "Wordle.h"

#include <iostream>

bool Wordle::isGuessInHistory(const std::string_view input) const {
    if (mGuessHistory.empty()) return false;

    for (const auto&[guess, statuses] : mGuessHistory) {
        if (guess == input) {
            return true;
        }
    }
    return false;
}

void Wordle::submitGuess(std::string guess, const std::vector<LetterStatus> &statuses) {
    mGuessHistory.emplace_back(guess, statuses);
    ++mGuesses;
    if (guess == mWord) {
        mWon = true;
    }
}
