#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <string>
#include <vector>

std::string preprocess(std::string text);

std::vector<std::string> splitWords(std::string text);

std::vector<std::string> filtered(
    const std::vector<std::string>& words
);

#endif