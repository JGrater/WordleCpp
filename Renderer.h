//
// Created by Jason Grater on 06/10/2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>

#include "Wordle.h"

namespace Renderer {

    static constexpr std::string RESET{"\033[0m"};
    static constexpr std::string GREEN{"\033[42;30m"};
    static constexpr std::string YELLOW{"\033[43;30m"};
    static constexpr std::string GREY{"\033[100;37m"};

    inline void renderWelcome() {
        std::cout << "Welcome to C++ Wordle.\nGuess the 5-letter word correctly to win!\n";
    }

    inline std::string getColour(const LetterStatus &letterStatus) {
        switch (letterStatus) {
            case correct:
                return GREEN;
            case present:
                return YELLOW;
            default:
                return GREY;
        }
    }

    inline void renderGuess(const guessHistory& guesses) {
        for (int i{0}; i < guesses.guess.length(); i++) {
            std::cout << getColour(guesses.statuses[i]) << " " << guesses.guess[i] << " " << RESET;
        }
    }

    inline void renderBoard(const std::vector<guessHistory>& guessHistory) {
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
