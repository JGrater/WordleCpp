//
// Created by JGrater on 05/10/2026.
//

#ifndef WORDLE_H
#define WORDLE_H

#include <vector>

static constexpr int MAX_GUESSES{6};

enum class LetterStatus {
    Correct,
    Present,
    Absent,
    Unset,
};

struct GuessHistory {
    std::string guess;
    std::vector<LetterStatus> statuses;
};

class Wordle {
public:
    explicit Wordle(const std::string_view word)
        : mWord{word} {}

    std::string_view getWord() const { return mWord; }
    const std::vector<GuessHistory>& getGuessHistory() const { return mGuessHistory; }
    int getRemainingGuesses() const { return MAX_GUESSES - mGuesses; };

    bool isGameWin() const { return mWon; };
    bool isGameOver() const { return mWon || mGuesses >= MAX_GUESSES; }
    bool isGuessInHistory(std::string_view input) const;
    std::vector<LetterStatus> evaluate(std::string_view input) const;
    void submitGuess(std::string guess, std::vector<LetterStatus> statuses);
private:
    std::string mWord{}; // init with random word from words.txt
    int mGuesses{0};
    std::vector<GuessHistory> mGuessHistory{};
    bool mWon{false};
};



#endif //WORDLE_H
