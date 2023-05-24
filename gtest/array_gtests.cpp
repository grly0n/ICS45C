#include <gtest/gtest.h>

#include <string>

#include "array.hpp"

using namespace std;

TEST(ArrayTests, Length) {
    Array<int> arr{3};
    EXPECT_EQ(arr.length(), 3);

    Array<string> arr2{10};
    EXPECT_EQ(arr2.length(), 10);

    EXPECT_EQ(Array<double>{}.length(), 0);
}

TEST(ArrayTests, CopyAssignment) {
    Array<int> arr{};
    Array<int> arr2{5};
    arr = arr2;
    EXPECT_EQ(arr.length(), arr2.length());

    Array<double> arr3{7};
    arr3 = arr3;
    EXPECT_EQ(arr3.length(), 7);
}

TEST(ArrayTests, Fill) {
    Array<int> arr{10};
    arr.fill(20);
    EXPECT_EQ(arr[0], 20);

    Array<double> arr2{5};
    arr2.fill(3.14);
    EXPECT_EQ(arr2[4], 3.14);

    Array<string> arr3{10};
    arr3.fill(string("hello"));
    EXPECT_EQ(arr3[1], string("hello"));
}

TEST(ArrayTests, OutOfBounds) {
    Array<double> arr{10};
    EXPECT_ANY_THROW(arr[10]);
}

TEST(ArrayTests, FillWithFn) {
    Array<int> arr{10};
    arr.fill(10);
    arr.fill_with_fn([](auto i){return i*i;});
    EXPECT_EQ(arr[2], 4);

}
