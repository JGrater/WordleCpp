#include "Renderer.h"
#include "Wordle.h"
#include "WordRepository.h"

#include <iostream>

bool verifyInput(const std::string_view input) {
    if (input.empty() || input.length() != 5) {
        std::cout << "Not a 5 letter word. Try again!\n";
        return false;
    }

    for (const auto letter : input) {
        if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z')) {
            std::cout << "Not a word. Try again!\n";
            return false;
        }
    }
    return true;
}

void gameLoop(const WordRepository& repo) {
    Wordle game{repo.getRandomWord()};

    do {
        std::string input = ConsoleInput::stringInput(std::format("\nEnter a 5-letter word ({} attempts left): ", game.getRemainingGuesses()));
        if (!verifyInput(input)) continue;

        input = Utils::toUpper(input);

        if (!repo.isValidWord(input)) {
            std::cout << "Not recognised. Try again!\n";
            continue;
        }
        if (game.isGuessInHistory(input)) {
            std::cout << "Already guessed. Try again!\n";
            continue;
        }

        game.submitGuess(input, game.evaluate(input));

        Renderer::renderBoard(game.getGuessHistory());
    } while (!game.isGameOver());
    Renderer::renderResult(game.isGameWin(), game.getWord());
}

bool doPlayAgain() {
    return ConsoleInput::charInput("Play again? (y/n):", "yn") == 'y';
}

void run(const WordRepository& repo) {
    Renderer::renderWelcome();
    while (true) {
        gameLoop(repo);
        if (!doPlayAgain()) {
            break;
        }
    }
}

int main() {
    const WordRepository wordRepository{};
    run(wordRepository);
    return 0;
}
