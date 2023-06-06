#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
    };
public:
    using value_type = T;

    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}
        ListIterator& operator++() {ptr = ptr->next; return *this;}
        ListIterator operator++(int) {ListIterator cpy = *this; ptr = ptr->next; return cpy;}
        T& operator*() const {return ptr.get()->data;}
        T* operator->() const {return *ptr.get()->data;}
        bool operator==(const ListIterator& other) const = default;
    private:
        std::shared_ptr<ListNode> ptr;
    };
    SetList() = default;
    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng),
                              std::bind_front(&SetList::insert, this));
    }
    ListIterator begin() {return ListIterator(head);}
    ListIterator end() {return ListIterator(nullptr);}

    bool contains(T const& value) {
        for(std::shared_ptr<ListNode> p = head; (p); p=p->next) 
            if (p->data == value) return true;
        return false;
    }

    ListIterator insert(T value) {
        if (!contains(value)) {
            ListNode newNode {.data = value, .next = head};
            head = std::move(std::make_shared<ListNode>(newNode));
        }
        return ListIterator(head);
    }
private:
    using iterator = ListIterator;
    static_assert(std::forward_iterator<iterator>);
    std::shared_ptr<ListNode> head = nullptr;
};
#endif
