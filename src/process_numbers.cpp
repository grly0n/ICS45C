#include <algorithm>
#include <iosfwd>
#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "process_numbers.hpp"

std::vector<int> get_int_vector(std::istream& input) {
    std::string line;
    std::getline(input, line);
    std::stringstream stream(line);
    return std::vector<int>(std::istream_iterator<int>(stream), {});
}

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
   std::vector<int> nums{get_int_vector(numbers)};
   std::sort(nums.begin(), nums.end());
   std::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(odds, " "), [](int i){return i % 2 != 0;});
   odds << '\n';
   std::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(evens, "\n"), [](int i){return i%2 == 0;});
}
