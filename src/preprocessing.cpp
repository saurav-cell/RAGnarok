#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include "../include/preprocessing.h"



using namespace std;
string preprocess(string text) {
    string cleaned = "";

    for (int i = 0; i < text.size(); i++) {
        char c = tolower(text[i]);

        if ((c >= 'a' && c <= 'z') || c == ' ') {
            cleaned += c;
        }
    }

    return cleaned;
}
// Split words
vector<string> splitWords(string text) {
    vector<string> words;
    string current = "";

    for (int i = 0; i < text.size(); i++) {
        if (text[i] != ' ') {
            current += text[i];
        } else {
            if (!current.empty()) {
                words.push_back(current);
                current = "";
            }
        }
    }

    if (!current.empty()) {
        words.push_back(current);
    }

    return words;
}

// Stopwords removal
vector<string> filtered(const vector<string>& words) {
    vector<string> stopwords = {
        "a","an","the","and","is","in","on","at","for","to","from",
        "of","with","by","this","that","it","as","be","are","was","were",
        "has","have","had","do","does","did","but","not","or","can"
    };

    vector<string> filteredWords;

    for (int i = 0; i < words.size(); i++) {
        bool isStopWord = false;

        for (int j = 0; j < stopwords.size(); j++) {
            if (words[i] == stopwords[j]) {
                isStopWord = true;
                break;
            }
        }

        if (!isStopWord) {
            filteredWords.push_back(words[i]);
        }
    }

    return filteredWords;
}
