//
// Created by JGrater on 05/10/2026.
//

#include "WordRepository.h"
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <ranges>
#include <filesystem>

void WordRepository::loadWords(const std::string& filepath) {
    if (!std::filesystem::exists(filepath)) throw std::runtime_error("File does not exist: " + filepath);

    std::ifstream inf(filepath);

    if (!inf) throw std::runtime_error("Could not open file " + filepath);

    std::string word;
    while (inf >> word) {
        mWords.push_back(word);
    }
}

bool WordRepository::isValidWord(const std::string_view word) const {
    if (std::ranges::find(mWords, word) != mWords.end()) { // Iterator contains, does not equal the end of vector
        return true;
    }
    return false;
}
