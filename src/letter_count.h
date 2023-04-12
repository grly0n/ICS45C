#include <iostream>
using namespace std;

int char_to_index(char ch) {
    if (ch == 'A') {
        return 0;
    } else if (ch == 'B') {
        return 1;
    } else if (ch == 'C') {
        return 2;
    } else if (ch == 'D') {
        return 3;
    } else if (ch == 'E') {
        return 4;
    } else if (ch == 'F') {
        return 5;
    } else if (ch == 'G') {
        return 6;
    } else if (ch == 'H') {
        return 7;
    } else if (ch == 'I') {
        return 8;
    } else if (ch == 'J') {
        return 9;
    } else if (ch == 'K') {
        return 10;
    } else if (ch == 'L') {
        return 11;
    } else if (ch == 'M') {
        return 12;
    } else if (ch == 'N') {
        return 13;
    } else if (ch == 'O') {
        return 14;
    } else if (ch == 'P') {
        return 15;
    } else if (ch == 'Q') {
        return 16;
    } else if (ch == 'R') {
        return 17;
    } else if (ch == 'S') {
        return 18;
    } else if (ch == 'T') {
        return 19;
    } else if (ch == 'U') {
        return 20;
    } else if (ch == 'V') {
        return 21;
    } else if (ch == 'W') {
        return 22;
    } else if (ch == 'X') {
        return 23;
    } else if (ch == 'Y') {
        return 24;
    } else if (ch == 'Z') {
        return 25;
    }
}

char index_to_char(int i) {
    if (i == 0) {
        return 'A';
    } else if (i == 1) {
        return 'B';
    } else if (i == 2) {
        return 'C';
    } else if (i == 3) {
        return 'D';
    } else if (i == 4) {
        return 'E';
    } else if (i == 5) {
        return 'F';
    } else if (i == 6) {
        return 'G';
    } else if (i == 7) {
        return 'H';
    } else if (i == 8) {
        return 'I';
    } else if (i == 9) {
        return 'J';
    } else if (i == 10) {
        return 'K';
    } else if (i == 11) {
        return 'L';
    } else if (i == 12) {
        return 'M';
    } else if (i == 13) {
        return 'N';
    } else if (i == 14) {
        return 'O';
    } else if (i == 15) {
        return 'P';
    } else if (i == 16) {
        return 'Q';
    } else if (i == 17) {
        return 'R';
    } else if (i == 18) {
        return 'S';
    } else if (i == 19) {
        return 'T';
    } else if (i == 20) {
        return 'U';
    } else if (i == 21) {
        return 'V';
    } else if (i == 22) {
        return 'W';
    } else if (i == 23) {
        return 'X';
    } else if (i == 24) {
        return 'Y';
    } else if (i == 25) {
        return 'Z';
    }
}

void count(string s, int counts[]) {
    for (int i = 0; i < int(s.size()); i++) {
        char ch = s[i];
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = toupper(ch);
            }
            int index = char_to_index(ch);
            counts[index]++;
        }
    }
}

void print_counts(int counts[], int len) {
    for (int i = 0; i < len; i++) {
        cout << index_to_char(i) << " " << counts[i] << endl;
    }
}
