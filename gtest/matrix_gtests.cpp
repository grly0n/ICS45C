#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <iostream>

#include "matrix.hpp"

using namespace std;

TEST(MatrixTests, RowsAndCols) {
    Matrix<int> mat{3, 2};
    EXPECT_EQ(mat.num_rows(), 3);
    EXPECT_EQ(mat.num_cols(), 2);

    Matrix<double> mat2{5, 1};
    EXPECT_EQ(mat2.num_rows(), 5);
    EXPECT_EQ(mat2.num_cols(), 1);

    Matrix<string> mat3;
    EXPECT_EQ(mat3.num_rows(), 0);
    EXPECT_EQ(mat3.num_cols(), 0);
}

TEST(MatrixTests, Index) {
    Matrix<int> mat{3, 2};
    EXPECT_EQ(mat[0].length(), 2);
    EXPECT_EQ(mat[1].length(), 2);
    EXPECT_EQ(mat[2].length(), 2);
    EXPECT_ANY_THROW(mat[3]);

    Matrix<double> mat2;
    EXPECT_ANY_THROW(mat2[0]);
}

TEST(MatrixTests, Fill) {
    Matrix<int> mat{3, 3};
    mat.fill(5);
    EXPECT_EQ(mat[0][0], 5);
    EXPECT_EQ(mat[2][2], 5);
    EXPECT_EQ(mat[1][1], 5);

    Matrix<double> mat2{3, 2};
    mat2.fill(2.5);
    EXPECT_EQ(mat2[0][0], 2.5);
    EXPECT_EQ(mat2[1][1], 2.5);
    EXPECT_EQ(mat2[2][1], 2.5);
}

TEST(MatrixTests, FillWithFn) {
    Matrix<int> mat{4, 4};
    mat.fill_with_fn([](int i, int j){return i+j;});
    EXPECT_EQ(mat[0][1], 1);
    EXPECT_EQ(mat[0][2], 2);
    EXPECT_EQ(mat[0][3], 3);
    EXPECT_EQ(mat[3][3], 6);

    Matrix<double> mat2{2, 3};
    mat2.fill_with_fn([](double i, double j){return i+j+0.5;});
    EXPECT_EQ(mat2[0][0], 0.5);
    EXPECT_EQ(mat2[0][1], 1.5);
    EXPECT_EQ(mat2[0][2], 2.5);
}

TEST(MatrixTests, Print) {
    stringstream out;
    Matrix<int> mat{4, 4};
    mat.fill_with_fn([](int i, int j){return i+j;});
    out << mat;
    EXPECT_EQ(out.str(), "0 1 2 3 \n1 2 3 4 \n2 3 4 5 \n3 4 5 6 \n");

    stringstream out2;
    Matrix<double> mat2;
    out2 << mat2;
    EXPECT_EQ(out2.str(), "");
}

