//
// Created by JGrater on 06/10/2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>

#include "Wordle.h"

namespace Renderer {

    static constexpr std::string_view RESET{"\033[0m"};
    static constexpr std::string_view GREEN{"\033[42;30m"};
    static constexpr std::string_view YELLOW{"\033[43;30m"};
    static constexpr std::string_view GREY{"\033[100;37m"};

    inline void renderWelcome() {
        std::cout << "Welcome to C++ Wordle.\nGuess the 5-letter word correctly to win!\n";
    }

    inline std::string_view getColour(const LetterStatus letterStatus) {
        switch (letterStatus) {
            case LetterStatus::Correct:
                return GREEN;
            case LetterStatus::Present:
                return YELLOW;
            default:
                return GREY;
        }
    }

    inline void renderGuess(const GuessHistory& guesses) {
        for (std::size_t i{0}; i < guesses.guess.length(); i++) {
            std::cout << getColour(guesses.statuses[i]) << " " << guesses.guess[i] << " " << RESET;
        }
    }

    inline void renderBoard(const std::vector<GuessHistory>& guessHistory) {
        for (auto const& guess : guessHistory) {
            renderGuess(guess);
            std::cout << std::endl;
        }
    }

    inline void renderResult(const bool won, const std::string_view word) {
        if (won) {
            std::cout << "You won!\n";
        } else {
            std::cout << "You lost! The word was " << word << "!\n";
        }
    }
}

#endif //RENDERER_H
