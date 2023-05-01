#include <iostream>
#include <utility>
#include "string.hpp"
using namespace std;

String::String(const char* s) : buf(strdup(s)) {}


String::String(const String& s) : buf(strdup(s.buf)) {}


String::String(int length) : buf(new char[length]) {}


String::String(String &&s) : buf(s.buf) {s.buf = nullptr;}


String &String::operator=(const String& s) {
    if (&s == this) return *this;
    if (buf) delete[] buf;
    buf = strdup(s.buf);
    return *this;
}


String &String::operator=(String &&s) {
    if (&s == this) return *this;
    delete[] buf;
    buf = s.buf;
    s.buf = nullptr;
    return *this;
}


void String::swap(String& s) {
    char* p = buf;
    buf = s.buf;
    s.buf = p;
    p = nullptr;
}


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
    for (; i < n; ++i)
        if (left[i] < right[i]) return -1;
        else if (left[i] > right[i]) return 1;
        else if (left[i] == '\0' && right[i] != '\0') return -1;
        else if (left[i] != '\0' && right[i] == '\0') return 1;
        else if (left[i] == '\0' && right[i] == '\0') return 0;
    return 0;
}


const char *String::strchr(const char *str, char c) {
    int len = strlen(str);
    for (int i = 0; i <= len; ++i)
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


int String::indexOf(char c) const {
    const char *o = strchr(buf, c);
    if (o != nullptr) return o-buf;
    else return -1;
}


int String::indexOf(const String& s) const {
    const char *o = strstr(buf, s.buf);
    if (o != nullptr) return o-buf;
    else return -1;
}


void String::reverse_cpy(char *dest, const char *src) {
    int j = 0, i = strlen(src)-1;
    for(; i >= 0; --i, ++j)
        dest[j] = src[i];
    dest[j] = '\0';
}


char &String::operator[](int index) {
    if (index < 0 || index >= strlen(buf)) {
        cout << "ERROR: Index out of bounds ";
        return buf[0];
    }
    return buf[index];
}


const char &String::operator[](int index) const {
    if (index < 0 || index > strlen(buf)) {
        cout << "ERROR: Index out of bounds ";
        return buf[0];
    }
    return buf[index];
}


bool String::operator==(const String& s) const {return (strcmp(buf, s.buf) == 0);}

bool String::operator!=(const String& s) const {return (strcmp(buf, s.buf) != 0);}

bool String::operator<(const String& s) const {return (strcmp(buf, s.buf) < 0);}

bool String::operator>(const String& s) const {return (strcmp(buf, s.buf) > 0);}

bool String::operator<=(const String& s) const {return (strcmp(buf, s.buf) <= 0);}

bool String::operator>=(const String& s) const {return (strcmp(buf, s.buf) >= 0);}


String String::reverse() const {
    String output(strlen(buf)+1);
    reverse_cpy(output.buf, buf);
    return output;
}


String String::operator+(const String& s) const {
    String output(strlen(buf) + strlen(s.buf) + 1);
    strcpy(output.buf, buf);
    strcat(output.buf, s.buf);
    return output;
}


String &String::operator+=(const String& s) {
    String temp(buf);
    if (buf) delete[] buf;
    buf = new char[strlen(temp.buf) + strlen(s.buf) + 1];
    strcpy(buf, temp.buf);
    strcat(buf, s.buf);
    return *this;
}


void String::print(ostream &out) const {
    out << buf;
}


ostream &operator<<(ostream &out, String s) {
    s.print(out);
    return out;
}

void String::read(istream &in) {
    if (buf) delete[] buf;
    char p[1024];
    in >> p;
    buf = strdup(p);
    }

istream &operator>>(istream &in, String &s) {
    s.read(in);
    return in;
}
