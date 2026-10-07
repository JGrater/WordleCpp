//
// Created by JGrater on 05/10/2026.
//

#include "Wordle.h"

#include <cassert>
#include <iostream>
#include <map>

bool Wordle::isGuessInHistory(const std::string_view input) const {
    return std::ranges::any_of(mGuessHistory, [&](const auto& entry) {
        return entry.guess == input;
    });
}

/**
     * Evaluates a guess against the wordle using a two-pass
     * algorithm: first mark exact position matches as CORRECT and
     * consume them from the per-letter remaining-count map built from the
     * wordle, then scan the remaining letters left-to-right marking
     * PRESENT only while that letter still has a positive remaining count.
     *
     * Both mWord and input must be the same length and
     * are compared in upper case.
     */
std::vector<LetterStatus> Wordle::evaluate(const std::string_view input) const {
    assert(input.size() == mWord.size());
    using enum LetterStatus;

    std::vector letters(mWord.size(),Unset);
    std::map<char, int> remainingCount{};

    for (std::size_t i{0}; i < mWord.length(); ++i) {
        const char wordChar{mWord[i]};
        const char guessChar{input[i]};
        if (wordChar == guessChar) {
            letters[i] = Correct;
        } else {
            // Record the remaining wordle char and increment its count in a map
            remainingCount[wordChar]++;
        }
    }

    for (std::size_t i{0}; i < mWord.length(); ++i) {
        // If letter status already set, continue
        if (letters[i] != Unset) continue;

        char guessChar{input[i]};
        // Get the count of remaining char, if not recorded default to 0
        const int count{remainingCount[guessChar]};

        if (count > 0) {
            letters[i] = Present;
            // Decrement the count of remaining recorded char
            remainingCount[guessChar]--;
        } else {
            letters[i] = Absent;
        }
    }
    return letters;
}


void Wordle::submitGuess(std::string guess, std::vector<LetterStatus> statuses) {
    if (guess == mWord) {
        mWon = true;
    }
    ++mGuesses;
    mGuessHistory.emplace_back(std::move(guess), std::move(statuses));
}
