#include "picture.hpp"
#include <iostream>
#include <utility>
using namespace std;

Picture::Picture() : head(nullptr), tail(nullptr) {}


Picture::Picture(const Picture& other) {
    if (other.head == nullptr) head = tail = nullptr;
    else {
        head = new ListNode;
        head->shape = other.head->shape->clone();
        head->next = other.head->next;
        head->prev = other.head->prev;
        ListNode* next = other.head->next;
        ListNode* temp = head;
        while (next != nullptr) {
            temp->next = new ListNode;
            temp->next->shape = next->shape->clone();
            temp->next->next = next->next;
            temp->next->prev = next->prev;
            temp = temp->next;
            next = next->next;
        }
        tail = temp;
    }
}

Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr, other.tail = nullptr;
}

void Picture::swap(Picture &other) {
    ListNode *h = head, *t = tail;
    head = other.head, tail = other.tail;
    other.head = h, other.tail = t;
    h = nullptr, t = nullptr;
}

Picture &Picture::operator=(const Picture& other) {
    if (&other == this) return *this;
    Picture dup(other);
    swap(dup);
    return *this;
}

Picture &Picture::operator=(Picture &&other) {
    swap(other);
    return *this;
}

void Picture::add(const Shape& shape) {
    ListNode *newNode = new ListNode;
    newNode->shape = shape.clone();
    newNode->prev = nullptr;
    newNode->next = head;
    if (head) head->prev = newNode;
    head = newNode;

    if (tail == nullptr) tail = newNode;
}

void Picture::print_all(ostream& out) const {
    for(ListNode *curr = tail; curr != nullptr; curr=curr->prev) {
        curr->shape->print(out);
        curr->shape->draw(out);
    }
}

void Picture::draw_all(ostream& out) const {
    ListNode *curr = tail;
    for(; curr != nullptr; curr=curr->prev) {
        curr->shape->draw(out);
    }
}

double Picture::total_area() const {
    double count{0.0};
    ListNode *curr = head;
    for(; curr != nullptr; curr=curr->next) {
        count += curr->shape->area();
    }
    return count;
}

Picture::~Picture() {
    ListNode *curr = head;
    while (curr != nullptr) {
        ListNode* temp = curr;
        delete curr->shape;
        curr = curr->next;
        delete temp;
    }
}
