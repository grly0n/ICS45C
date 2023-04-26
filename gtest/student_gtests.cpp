#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result[10];
    EXPECT_EQ(String::strncpy(result, "foo", 9), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strncpy(result, "a", 9), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strncpy(result, "", 9), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char result1[10] = "foo";
    EXPECT_EQ(String::strcat(result1, "bar"), result1);
    EXPECT_STREQ(result1, "foobar");

    char result2[10] = "a";
    EXPECT_EQ(String::strcat(result2, "bcdefg"), result2);
    EXPECT_STREQ(result2, "abcdefg");

    char result3[10] = "";
    EXPECT_EQ(String::strcat(result3, ""), result3);
    EXPECT_STREQ(result3, "");

}

TEST(StringFunction, strncat) {
    char result1[20] = "To be ";
    EXPECT_EQ(String::strncat(result1, "or not to be", 6), result1);
    EXPECT_STREQ(result1, "To be or not");

    char result2[20] = "C++ is ";
    EXPECT_EQ(String::strncat(result2, "easy", 6), result2);
    EXPECT_STREQ(result2, "C++ is easy");

    char result3[10] = "Nothing";
    EXPECT_EQ(String::strncat(result3, " do not append", 0), result3);
    EXPECT_STREQ(result3, "Nothing");
}

TEST(StringFunction, strcmp) {
    char left1[10] = "Apple";
    char right1[10] = "Orange";
    EXPECT_LT(String::strcmp(left1, right1), 0);

    char right2[20] = "ApplePie";
    EXPECT_LT(String::strcmp(left1, right2), 0);

    char left2[30] = "ApplePieWithIceCream";
    EXPECT_GT(String::strcmp(left2, right2), 0);

    char left3[10] = "Pineapple";
    EXPECT_GT(String::strcmp(left3, right2), 0);

    char right3[10] = "Pineapple";
    EXPECT_EQ(String::strcmp(left3, right3), 0);
}

TEST(StringFunction, strncmp) {
    char left1[5] = "R2D2";
    char right1[5] = "R2A6";
    EXPECT_EQ(String::strncmp(left1, right1, 2), 0);
    EXPECT_GT(String::strncmp(left1, right1, 4), 0);

    char left2[5] = "C3PO";
    EXPECT_LT(String::strncmp(left2, right1, 1), 0);

    char right2[20] = "C3PO's builder";
    EXPECT_EQ(String::strncmp(left2, right2, 4), 0);
    EXPECT_LT(String::strncmp(left2, right2, 5), 0);
}

TEST(StringFunction, reverse_cpy) {
    char dest[10];
    String::reverse_cpy(dest, "abcdefg");
    EXPECT_STREQ(dest, "gfedcba");

    String::reverse_cpy(dest, "");
    EXPECT_STREQ(dest, "");

    String::reverse_cpy(dest, "a");
    EXPECT_STREQ(dest, "a");
    
}

TEST(StringFunction, strchr) {
    char test1[30] = "There is a z in this string";
    EXPECT_EQ(String::strchr(test1, 'z'), &test1[11]);

    char test2[10] = "abcdefg";
    EXPECT_EQ(String::strchr(test2, 'g'), &test2[6]);

    char test3[40] = "This test will return a nullptr";
    EXPECT_EQ(String::strchr(test3, 'x'), nullptr);

    char test4[10] = "Not null";
    EXPECT_EQ(String::strchr(test4, '\0'), &test4[8]);
}

TEST(StringFunction, strstr) {
    char test1[30] = "This is a simple string";
    EXPECT_EQ(String::strstr(test1, "simple"), &test1[10]);

    char test2[30] = "Functions like strchr";
    EXPECT_EQ(String::strstr(test2, "e"), &test2[13]);

    char test3[30] = "The word is not in here";
    EXPECT_EQ(String::strstr(test3, "function"), nullptr);

    char test4[10] = "Not null";
    EXPECT_EQ(String::strstr(test4, ""), &test4[0]);
}

//TEST(StringFunction, indexOf) {
//    String test1{"This is a certified hood classic"};
//    EXPECT_EQ(test1.indexOf(String("")), 0);
//    EXPECT_EQ(test1.indexOf('z'), -1);
//    EXPECT_EQ(test1.indexOf(String("fooooooooo")), -1);
//}
