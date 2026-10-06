#include <cassert>
#include <iostream>
#include <map>

#include "Renderer.h"
#include "Wordle.h"
#include "WordRepository.h"

std::vector<LetterStatus> evaluate(const std::string_view word, const std::string input) {
    assert(word.size() == input.size());

    std::vector letters(5,null);
    std::map<char, int> remainingCount{};

    for (int i{0}; i < word.length(); ++i) {
        const char wordChar{word[i]};
        const char guessChar{input[i]};
        if (wordChar == guessChar) {
            letters[i] = correct;
        } else {
            // Record the wordle char and count in a map, this is to account for duplication
            remainingCount[wordChar]++;
        }
    }

    for (int i{0}; i < word.length(); ++i) {
        // if letter status already set, continue
        if (letters[i] != null) continue;

        char guessChar{input[i]};
        // get count of remaining char, if not recorded default to 0
        const int count{remainingCount[guessChar] ? remainingCount[guessChar] : 0};

        if (count > 0) {
            letters[i] = present;
            // decrement count of recorded remaining char
            remainingCount[guessChar]--;
        } else {
            letters[i] = absent;
        }
    }
    return letters;
}

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
        std::string input = ConsoleInput::string_input(std::format("\nEnter a 5-letter word ({} attempts left): ", game.getRemainingGuesses()));
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

        game.submitGuess(input, evaluate(game.getWord(), input));

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
