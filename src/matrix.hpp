#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <iomanip>
#include <sstream>

#include "array.hpp"

template <typename T>
class Matrix {
public:
    Matrix() : rows{0}, cols{0} {}

    Matrix(int rows, int cols) : rows{rows}, cols{cols} {
        Array<Array<T>> temp(rows);
        temp.fill(Array<T>(cols));
        data = temp;
    }

    Array<T>& operator[](int row) {return data[row];}
    const Array<T>& operator[](int row) const {return data[row];}

    int num_rows() const {return rows;}
    int num_cols() const {return cols;}

    void fill(const T& val) {
        for(int i = 0; i < rows; ++i) data[i].fill(val);
    }

    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }

private:
    int rows, cols;
    Array<Array<T>> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    std::stringstream temp;
    temp << std::setprecision(2);
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            temp << matrix[i][j] << ' ';
        }
        temp << '\n';
    }
    out << temp.str();
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for(int i = 0; i < matrix.num_rows(); ++i) {
        in >> matrix[i];
    }
    return in;
}

#endif
