#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>
#include <iostream>

template <typename Key, typename Value>
class MapArray {
public:
    using value_type = std::pair<Key, Value>;
    class ArrayIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr) : ptr(ptr) {};
        ArrayIterator& operator++() {++ptr; return *this;}
        ArrayIterator& operator--() {--ptr; return *this;}
        ArrayIterator operator++(int) {ArrayIterator cpy = *this; ptr++; return cpy;}
        ArrayIterator operator--(int) {ArrayIterator cpy = *this; ptr--; return cpy;}
        ArrayIterator& operator +=(difference_type d) {ptr+=d; return *this;}
        ArrayIterator& operator -=(difference_type d) {ptr-=d; return *this;}
        friend ArrayIterator operator+(ArrayIterator it, difference_type d) {return it+=d;}
        friend ArrayIterator operator+(difference_type d, ArrayIterator it) {return it+=d;}
        friend ArrayIterator operator-(ArrayIterator it, difference_type d) {return it-=d;}
        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs) {
           return lhs.ptr - rhs.ptr;
        }
        auto operator<=>(const ArrayIterator& other) const = default;
        std::pair<Key, Value>& operator*() const {return *ptr;}
        std::pair<Key, Value>* operator->() const {return ptr;}
        std::pair<Key, Value>& operator[](difference_type d) const {return ptr[d];}
    private:
        std::pair<Key, Value>* ptr;
    };
    using iterator = ArrayIterator;
    ArrayIterator begin() {
    if (!data.size()) return ArrayIterator();
    else return ArrayIterator(&data[0]);}
    ArrayIterator end() {
    if (!data.size()) return ArrayIterator();
    else return ArrayIterator(&data[data.size()]);}
    Value& operator[](const Key& key) {
        for (auto& e : data) if (e.first == key) return e.second;
        std::pair<Key, Value> newKey (key, 0);
        data.emplace(std::upper_bound(data.begin(), data.end(), newKey), newKey);
        for (auto& e : data) if (e.first == key) return e.second;
        throw "Unexpected error";
        
    }
private:
    std::vector<std::pair<Key, Value>> data;
    static_assert(std::random_access_iterator<iterator>);
};
#endif
