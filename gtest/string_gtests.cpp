#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

#include "string.hpp"

using namespace std;

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);
    
}

TEST(StringClass, Print) {
    String s("foo");
    stringstream out;
    s.print(out);
    EXPECT_STREQ(out.str().c_str(), "foo");

    stringstream out2;
    String().print(out2);
    EXPECT_STREQ(out2.str().c_str(), "");

    stringstream out3;
    out3 << s << s << String("bar");
    EXPECT_STREQ(out3.str().c_str(), "foofoobar");
}

TEST(StringClass, Comparisons) {
    EXPECT_LT(String("aaaa"), String("aaab"));
    EXPECT_LE(String("aaaa"), String("aaab"));
    EXPECT_EQ(String("foo"), String("foo"));
    EXPECT_NE(String("foo"), String("fooo"));
}

TEST(StringClass, Assignment) {
    String s("test"), t("foo");

    s = t;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = s;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = String();
    EXPECT_EQ(s, String());
    EXPECT_EQ(s.size(), 0);
}

TEST(StringClass, InBounds) {
    String s("hello");
    EXPECT_TRUE(s.in_bounds(0));
    EXPECT_TRUE(s.in_bounds(4));
    EXPECT_FALSE(s.in_bounds(5));
    EXPECT_FALSE(s.in_bounds(-1));
}

TEST(StringClass, Indexing) {
    String s("Indexing this string");
    EXPECT_EQ(s[0], 'I');
    EXPECT_EQ(s[s.size()-1], 'g');
    EXPECT_EQ(s[4], 'x');

    //String t("");
    //EXPECT_EQ(t[0], '\0');
}

TEST(StringClass, Reverse) {
    stringstream out;
    String s("reversed"), t{s.reverse()};
    t.print(out);
    EXPECT_EQ(out.str(), "desrever");

    stringstream out2;
    String a, b{a.reverse()};
    b.print(out2);
    EXPECT_EQ(out2.str(), "");
}

TEST(StringClass, IndexOfChar) {
    String test("test string");
    EXPECT_EQ(test.indexOf('r'), 7);
    EXPECT_EQ(test.indexOf('\0'), -1);

    String empty("");
    EXPECT_EQ(empty.indexOf('\0'), 0);
    EXPECT_EQ(empty.indexOf('A'), -1);
}

TEST(StringClass, IndexOfString) {
    String test("A simple ");
    String find("string");
    test += find;
    EXPECT_EQ(test.indexOf(find), 9);
    EXPECT_EQ(test.indexOf(String("")), 0);

    String empty;
    EXPECT_EQ(empty.indexOf(String()), 0);
}
