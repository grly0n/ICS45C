#include "list.hpp"
#include <string.h>
#include <iostream>
using namespace std;

list::Node* list::from_string(const char* s) {
    Node* head = nullptr;
    for (int i = strlen(s)-1; i >= 0; --i) {
        Node* newNode = new Node;
        newNode->data = s[i];
        newNode->next = head;
        head = newNode;
    }
    return head;
}

void list::free(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}


void list::print(ostream& out, Node* head) {
    Node* current = head;
    for (; current != nullptr; current = current->next)
        out << current->data;
}


int list::length(Node* head) {
    if (head == nullptr) return 0;
    else return 1 + list::length(head->next);
}


list::Node* list::copy(Node* head) {
    return !head ? nullptr : new Node{head->data, list::copy(head->next)};
}


int list::compare(Node* lhs, Node* rhs) {
    Node* l = lhs;
    Node* r = rhs;
    for(; l != nullptr && r != nullptr; l=l->next, r=r->next)
        if (l->data < r->data) return -1;
        else if (l->data > r->data) return 1;
    if (l == nullptr && r != nullptr) return -1;
    else if (l != nullptr && r == nullptr) return 1;
    else return 0;
}


int list::compare(Node* lhs, Node* rhs, int n) {
    Node* r = rhs;
    Node* l = lhs;
    for (int i = 0; i < n; ++i, l=l->next, r=r->next)
        if (l == nullptr && r != nullptr) return -1;
        else if (l != nullptr && r == nullptr) return 1;
        else if (l == nullptr && r == nullptr) return 0;
        else if (l->data < r->data) return -1;
        else if (l->data > r->data) return 1;
    return 0;
}


list::Node* list::reverse(Node* head) {
    Node* original = head;
    Node* newHead = nullptr;
    for(; original != nullptr; original=original->next) {
        Node* newNode = new Node;
        newNode->data = original->data;
        newNode->next = newHead;
        newHead = newNode;
    }
    return newHead;
}


list::Node* list::append(Node* lhs, Node* rhs) {
    Node* newNode = nullptr;
    if (lhs == nullptr && rhs == nullptr) return nullptr;
    else if (lhs == nullptr && rhs != nullptr) newNode = new Node{rhs->data, list::append(lhs, rhs->next)};
    else newNode = new Node{lhs->data, list::append(lhs->next, rhs)};
    return newNode;
}


int list::index(Node* head, Node* node) {
    int count = 0;
    for(Node* p = head; p != nullptr; p=p->next)
        if (p == node) return count;
        else ++count;
    return -1;
}


list::Node* list::find_char(Node* head, char c) {
    if (!c) return head;
    for(Node* p = head; p != nullptr; p=p->next)
        if (p->data == c) return p;
    return nullptr;
}


list::Node* list::find_list(Node* haystack, Node* needle) {
    int len = list::length(needle);
    if (len == 0) return haystack;
    for(Node* p = haystack; (p = find_char(p, needle->data)); p=p->next)
        if (list::compare(p, needle, len) == 0) return p;
    return nullptr;
}


list::Node* list::nth(Node* head, int n) {
    return !n ? head : list::nth(head->next, n-1);
}


list::Node* list::last(Node* head) {
    return !head->next ? head : list::last(head->next);
}
