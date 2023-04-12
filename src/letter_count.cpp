#include <iostream>
using namespace std;
#include "letter_count.h"

constexpr int N_CHARS = ('Z'-'A'+1);

int main() {
    int char_count[N_CHARS] = {};
    cout << char_count[0] << endl;
    string line;
    while (getline(cin, line)) {
        count(line, char_count);
        print_counts(char_count, N_CHARS);
    }
    return 0;
}
