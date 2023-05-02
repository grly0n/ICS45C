#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <iostream>

#include "string.hpp"

using namespace std;

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);

    String u = s;
    EXPECT_EQ(u.size(), 5);
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

TEST(StringClass, Reverse) {
    String s("reversed"), t;
    t = s.reverse();
    EXPECT_EQ(t.size(), s.size());

    String a("");
    t = a.reverse();
    EXPECT_EQ(t.size(), a.size());
}

TEST(StringClass, Plus) {
    String s("First"), t("Second");
    String u = s + t;
    EXPECT_EQ(u.size(), 11);

    String a("foo"), b("bar");
    a += b;
    EXPECT_EQ(a.size(), 6);

    String c("Nothing"), d;
    c += d;
    EXPECT_EQ(c.size(), 7);
}
