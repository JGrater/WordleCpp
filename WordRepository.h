//
// Created by Jason Grater on 05/10/2026.
//

#ifndef WORDREPOSITORY_H
#define WORDREPOSITORY_H
#include "Common.h"
#include <vector>


class WordRepository {
public:
    WordRepository() { loadWords("assets/words.txt"); }

    std::vector<std::string> getWords() const { return mWords; }
    std::string_view getRandomWord() const { return mWords[Random::get<std::size_t>(0, mWords.size()-1)]; }
    bool isValidWord(std::string_view word) const;

private:
    std::vector<std::string> mWords;

    void loadWords(const std::string &filepath);
};



#endif //WORDREPOSITORY_H
