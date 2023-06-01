#include "mapset.hpp"

#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>

std::string to_lowercase(const std::string& str) {
    std::string output(str);
    std::transform(str.cbegin(), str.cend(), output.begin(), [](unsigned char c){return std::tolower(c);});
    return output;
}

void print(const std::string& str) {std::cout << to_lowercase(str) << ' ';}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> output;
    std::copy(std::istream_iterator<std::string>(stopwords), std::istream_iterator<std::string>(), std::inserter(output, output.begin()));
    std::set<std::string> test;
    std::transform(begin(output), end(output), std::inserter(test, begin(test)), to_lowercase);
    //std::for_each(output.begin(), output.end(), [](std::string str){return to_lowercase(str);});
    return test;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> output;
    std::for_each(std::istream_iterator<std::string>(document), std::istream_iterator<std::string>(),
        [&](std::string str){if (stopwords.find(to_lowercase(str)) == stopwords.end()) ++output[to_lowercase(str)];});
    return output;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) output << word << " " << count << std::endl;
}
