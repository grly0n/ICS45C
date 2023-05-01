#include <iostream>
#include "string.hpp"
using namespace std;

String::String(const char* s) : buf(strdup(s)) {}

int String::strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

char *String::strcpy(char* dest, const char* src) {
    int srcLength = strlen(src), i = 0;
    for ( ; i < srcLength; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

String::~String() {
    delete[] buf;
}
char *String::strdup(const char* src) {
    return strcpy(new char[strlen(src)+1], src);
}
