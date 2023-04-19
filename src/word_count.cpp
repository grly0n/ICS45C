#include <iostream>
#include <fstream>
#include "word_count.h"
using namespace std;

void to_lowercase(string& str) {
    for (int i = 0; i < int(str.length()); ++i) {
        if (isupper(str[i])) {
            str[i] += 32;
        }
    }
}

set<string> load_stopwords(istream& stopwords) {
    string word;
    set<string> S;
    while (stopwords >> word) {
        to_lowercase(word);
        S.insert(word);
    }
    return S;
}

map<string, int> count_words(istream& document, const set<string>& stopwords) {
    map<string, int> frequency;
    string word;
    while (document >> word) {
        to_lowercase(word);
        if (frequency.find(word) != frequency.end()) {
            ++frequency[word];
        } else if (stopwords.find(word) == stopwords.end()) {
            frequency[word] = 1;
        }
    }
    return frequency;
}      

void output_word_counts(const map<string, int>& word_counts, ostream& output) {
    for (auto word : word_counts) {
        output << word.first << " " << word.second << endl;
    }
}
