#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include <iosfwd>
#include <map>
#include <set>
#include <string>

void to_lowercase(std::string& str);

std::set<std::string> load_stopwords(std::istream& stopwords);

std::map<std::string, int> count_words(std::istream& document,
                                        const std::set<std::string>& stopwords);

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output);

#endif
