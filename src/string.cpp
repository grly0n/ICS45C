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
    for (; i < srcLength; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *String::strncpy(char* dest, const char* src, int n) {
    int srcLength = strlen(src), i = 0;
    for (; i < srcLength && i < n; ++i)
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


int String::size() const {
    return strlen(buf);
}


char *String::strcat(char *dest, const char *src) {
    int destLength = strlen(dest), i = destLength;
    for (; src[i - destLength] != '\0'; ++i)
        dest[i] = src[i - destLength];
    dest[i] = '\0';
    return dest;
}


char *String::strncat(char *dest, const char *src, int n) {
    int destLength = strlen(dest), i = destLength;
    for (; src[i - destLength] != '\0' && i - destLength < n; ++i)
        dest[i] = src[i - destLength];
    dest[i] = '\0';
    return dest;
}


int String::strcmp(const char* left, const char* right) {
    int i = 0;
    for (; left[i] != '\0'; ++i)
        if (left[i] < right[i]) return -1;
        else if (left[i] > right[i]) return 1;
    if (left[i] == '\0' && right[i] != '\0') return -1;
    else if (left[i] != '\0' && right[i] == '\0') return 1;
    else return 0;
}


int String::strncmp(const char* left, const char* right, int n) {
    int i = 0;
    for (; left[i] != '\0' && i < n; ++i)
        if (left[i] < right[i]) return -1;
        else if (left[i] < right[i]) return 1;
        else if (left[i] == '\0' && right[i] != '\0') return -1;
        else if (left[i] != '\0' && right[i] == '\0') return 1;
        else if (left[i] == '\0' && right[i] == '\0') return 0;
    return 0;
}


const char *String::strchr(const char *str, char c) {
    int i = 0;
    for (; str[i] != '\0'; ++i)
        if (str[i] == c) return &str[i];
    if (str[i] == c) return &str[i];
    return nullptr;
}


const char *String::strstr(const char *haystack, const char *needle) {
    int len = strlen(needle);
    if (len == 0) return &haystack[0];

    for (const char* p = haystack; (p = strchr(p, needle[0])); ++p)
        if (strncmp(p, needle, len) == 0)
            return p;
    return nullptr;
}


void String::reverse_cpy(char *dest, const char *src) {
    int j = 0, i = strlen(src)-1;
    for(; i >= 0; --i, ++j)
        dest[j] = src[i];
    dest[j] = '\0';
}
