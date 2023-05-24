#ifndef INT_ARRAY_HPP
#define INT_ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

class Array {
public:
    Array() : len{0}, buf{nullptr} {}

    explicit Array(int len) : len{len}, buf{new int[len]} {}

    Array(const Array& other) : len{other.len}, buf{new int[other.len]} {
        for (int i = 0; i < len; ++i)
            buf[i] = other.buf[i];
    }

    Array(Array&& other) noexcept : len{other.len}, buf{other.buf} {other.buf = nullptr;}

    friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    Array& operator=(const Array& other) {
        Array temp(other);
        swap(*this, temp);
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~Array() {delete[] buf;}

    int length() const {
        return len;
    }

    int& operator[](int index) {
        if (!in_bounds(index)) throw std::string("index out of bounds");
        else return buf[index];
    }

    const int& operator[](int index) const {
        if (!in_bounds(index)) throw std::string("index out of bounds");
        else return buf[index];
    }

    void fill(int val) {
        for (int i = 0; i < len; ++i)
            buf[i] = val;
    }

private:
    int len;
    int* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

inline std::ostream& operator<<(std::ostream& out, const Array& array) {
    std::stringstream temp;
    temp << std::setprecision(2) << std::fixed << std::right;

    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }

    out << temp.str();
    return out;
}


inline std::istream& operator>>(std::istream& in, Array& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif
