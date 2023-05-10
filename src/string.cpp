#include <iostream>
#include "string.hpp"
#include "list.hpp"
using namespace std;

String::String(const char *s) : head{list::from_string(s)} {}

String::String(const String &s) : head{list::copy(s.head)} {}

String::String(String &&s) : head(s.head) {s.head = nullptr;}

void String::swap(String &s) {
    list::Node* p = head;
    head = s.head;
    s.head = p;
    p = nullptr;
}

String &String::operator=(const String &s) {
    if (&s == this) return *this;
    if (head) list::free(head);
    head = list::copy(s.head);
    return *this;
}

String &String::operator=(String &&s) {
    if (&s == this) return *this;
    list::free(head);
    head = s.head;
    s.head = nullptr;
    return *this;
}

bool String::in_bounds(int index) const {
    return index >= 0 && index < size();
}

char String::operator[](int index) const {
    if (in_bounds(index)) {
        list::Node* p = list::nth(head, index);
        return p->data;
    } else {
        cout << "ERROR: Index out of bounds ";
        return !head ? '\0' : head->data;
    }
}

int String::size() const {return list::length(head);}

String String::reverse() const {
    list::Node* reverseCopyHead{list::reverse(head)};
    return String{reverseCopyHead};
}

int String::indexOf(char c) const {
    if (!head && !c) return 0;
    list::Node* p = list::find_char(head, c);
    return !p ? -1 : list::index(head, p);
}

int String::indexOf(const String &s) const {
    if (!head && !s.head) return 0;
    list::Node* p = list::find_list(head, s.head);
    return !p ? -1 : list::index(head, p);
}


bool String::operator==(const String& s) const {return list::compare(head, s.head) == 0;}

strong_ordering String::operator<=>(const String &s) const {
    return list::compare(head, s.head) <=> 0;
}

String String::operator+(const String& s) const {
    String newString{list::append(head, s.head)};
    return newString;
}

String &String::operator+=(const String& s) {
    String newString{list::append(head, s.head)};
    swap(newString);
    return *this;
}

void String::print(ostream &out) const {
    list::print(out, head);
}

void String::read(istream &in) {
    if (head) list::free(head);
    char p[1024];
    in >> p;
    head = list::from_string(p);
}

String::~String() {list::free(head);}

String::String(list::Node* head) : head{head} {}

ostream &operator<<(ostream &out, const String &s) {
    s.print(out);
    return out;
}

istream &operator>>(istream &in, String &s) {
    s.read(in);
    return in;
}
