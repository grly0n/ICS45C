#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

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

TEST(StringFunction, strdup) {
    char* result1 = String::strdup("hello");
    EXPECT_STREQ(result1, "hello");
    delete[] result1;

    char* result2 = String::strdup("");
    EXPECT_STREQ(result2, "");
    delete[] result2;

    char* result3 = String::strdup("A very long string with spaces and $p3c1@l characters!");
    EXPECT_STREQ(result3, "A very long string with spaces and $p3c1@l characters!");
    delete[] result3;
}

TEST(StringFunction, strncpy) {
    char result[10];
    EXPECT_EQ(String::strncpy(result, "foo", 9), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strncpy(result, "Hello!", 5), result);
    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char result1[20] = "Hello";
    EXPECT_EQ(String::strcat(result1, " world!"), result1);
    EXPECT_STREQ(result1, "Hello world!");

    char result2[7] = "foo";
    EXPECT_EQ(String::strcat(result2, "bar"), result2);
    EXPECT_STREQ(result2, "foobar");

    char result3[10] = "Just this";
    EXPECT_EQ(String::strcat(result3, ""), result3);
    EXPECT_STREQ(result3, "Just this");
}

TEST(StringFunction, strncat) {
    char result1[12] = "Hello ";
    EXPECT_EQ(String::strncat(result1, "there's treasure!", 5), result1);
    EXPECT_STREQ(result1, "Hello there");

    char result2[7] = "foo";
    EXPECT_EQ(String::strncat(result2, "bar", 6), result2);
    EXPECT_STREQ(result2, "foobar");

    char result3[10] = "";
    EXPECT_EQ(String::strncat(result3, "", 3), result3);
    EXPECT_STREQ(result3, "");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("hello", "hello"), 0);
    EXPECT_LT(String::strcmp("testa", "testb"), 0);
    EXPECT_GT(String::strcmp("testing", "test"), 0);
    EXPECT_LT(String::strcmp("test", "testing"), 0);
    EXPECT_LT(String::strcmp("", "literally anything"), 0);
    EXPECT_GT(String::strcmp("random", ""), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("Hello world", "Hello", 5), 0);
    EXPECT_LT(String::strncmp("R2D2", "R2E2", 4), 0);
    EXPECT_EQ(String::strncmp("This is a string", "Albuquerque", 0), 0);
    EXPECT_GT(String::strncmp("testing", "test", 10), 0);
    EXPECT_EQ(String::strncmp("foolish", "foolish", 20), 0);

    EXPECT_LT(String::strncmp("test", "testa", 5), 0);
    EXPECT_LT(String::strncmp("test", "testa", 10), 0);
    EXPECT_LT(String::strncmp("", ".", 1), 0);
    EXPECT_GT(String::strncmp("aaz", "aaba", 3), 0);
    EXPECT_GT(String::strncmp("nope", "nopa", 4), 0);
}

TEST(StringFunction, reverse_cpy) {
    char dest[30];
    String::reverse_cpy(dest, "abcdefg");
    EXPECT_STREQ(dest, "gfedcba");

    String::reverse_cpy(dest, "");
    EXPECT_STREQ(dest, "");

    String::reverse_cpy(dest, "a man a plan a canal panama");
    EXPECT_STREQ(dest, "amanap lanac a nalp a nam a");
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
