#include <iostream>

using namespace std;

#include "string.hpp"

String::String(const char *s) {
    if (strlen(s) > MAXLEN-1) {
        cout << "ERROR: String Capacity Exceeded" << endl;
    } else {
        strncpy(buf, s, MAXLEN-1);
    }
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for ( ; src[i] != '\0' && i < n; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

String::String(const String &s) {
    strcpy(buf, s.buf);
}

char *String::strcpy(char *dest, const char *src) {
    int srcLength = strlen(src), i = 0;
    for ( ; i < srcLength; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

String::~String() {
    //cout << "String " << buf << " is destructing" << endl;
}

String &String::operator=(const String &s) {
    strcpy(buf, s.buf);
    return *this;
}

int String::strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

int String::size() const {
    return strlen(buf);
}

void String::print(ostream &out) const {
    out << buf;
}

ostream &operator<<(ostream &out, const String &s) {
    s.print(out);
    return out;
}

void String::read(istream &in) {
    in >> buf;
}

istream &operator>>(istream &in, String &s) {
    s.read(in);
    return in;
}

char *String::strcat(char *dest, const char *src) {
    int destLength = strlen(dest), srcLength = strlen(src);
    int i = destLength;
    for ( ; i < destLength + srcLength; ++i)
    {
        dest[i] = src[i - destLength];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int destLength = strlen(dest), srcLength = strlen(src);
    int i = destLength;
    
    if (n < srcLength) {
        for ( ; i < destLength + n; ++i) {
            dest[i] = src[i - destLength];
        }
        dest[i] = '\0';
        return dest;
    } else {
        return strcat(dest, src);
    }
}

String String::operator+(const String &s) const {
    if (s.size() + size() >= MAXLEN-1) {
        cout << "ERROR: String Capacity Exceeded" << endl;
        return *this;
    } else {
        String output(buf);
        strncat(output.buf, s.buf, MAXLEN-1);
        return output;
    }
}

String &String::operator+=(const String &s) {
    if (s.size() + size() >= MAXLEN-1) {
        cout << "ERROR: String Capacity Exceeded" << endl;
        return *this;
    } else {
        strncat(buf, s.buf, MAXLEN-1);
        return *this;
    }
}

int String::strcmp(const char *left, const char *right) {
    int leftLength = strlen(left);
    for (int i = 0; i <= leftLength; ++i) {
        if (left[i] < right[i]) {
            return -1;
        } else if (left[i] > right[i]) {
            return 1;
        } else if (left[i] == '\0' && right[i] != '\0') {
            return -1;
        } else if (left[i] != '\0' && right[i] == '\0') {
            return 1;
        } else if (left[i] == '\0' && right[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

int String::strncmp(const char *left, const char *right, int n) {
    int i = 0;
    if (n == 0)
        return 0;
    for ( ; i < n; ++i) {
        if (left[i] < right[i]) {
            return -1;
        } else if (left[i] == '\0' && right[i] != '\0') {
            return -1;
        } else if (left[i] > right[i]) {
            return 1;
        } else if (left[i] != '\0' && right[i] == '\0') {
            return 1;
        } else if (left[i] == '\0' && right[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

bool String::operator==(const String &s) const {
    return (strcmp(buf, s.buf) == 0);
}

bool String::operator!=(const String &s) const {
    return (strcmp(buf, s.buf) != 0);
}

bool String::operator>(const String &s) const {
    return (strcmp(buf, s.buf) > 0);
}

bool String::operator<(const String &s) const {
    return (strcmp(buf, s.buf) < 0);
}

bool String::operator<=(const String &s) const {
    return (strcmp(buf, s.buf) <= 0);
}

bool String::operator>=(const String &s) const {
    return (strcmp(buf, s.buf) >= 0);
}

void String::reverse_cpy(char *dest, const char *src) {
    int j = 0, i = strlen(src)-1;
    for ( ; i >= 0; --i, ++j) {
        dest[j] = src[i];
    }
    dest[j] = '\0';
}

String String::reverse() const {
    String output = String();
    reverse_cpy(output.buf, buf);
    return output;
}

const char *String::strchr(const char *str, char c) {
    int len = strlen(str);
    for (int i = 0; i <= len; ++i)
        if (str[i] == c)
            return &str[i];
    return nullptr;
}        

const char *String::strstr(const char *haystack, const char *needle) {
    int len = strlen(needle);
    if (len == 0)
        return &haystack[0];

    for (const char * p = haystack; (p = strchr(p, needle[0])); ++p)
        if (strncmp(p, needle, len) == 0)
            return p;
    return nullptr;
}


int String::indexOf(char c) const {
    const char *o = strchr(buf, c);
    if (o != nullptr)
        return o-buf;
    else
        return -1;
}

int String::indexOf(const String &s) const {
    const char *o = strstr(buf, s.buf);
    if (o != nullptr)
        return o-buf;
    else
        return -1;
}

char &String::operator[](int index) {
    if (index < 0 || index >= strlen(buf)) {
        cout << "ERROR: Index Out Of Bounds" << endl;
        return buf[0];
    } else {
        return buf[index];
    }
}
