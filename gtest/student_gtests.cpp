#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);

    Node* const empty = list::from_string("");
    EXPECT_EQ(list::length(empty), 0);
    list::free(empty);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.

TEST(ListTests, Print) {
    stringstream output;
    Node* const head = list::from_string("Hello there");
    list::print(output, head);
    EXPECT_EQ(output.str(), "Hello there");
    list::free(head);

    stringstream output2;
    Node* const empty = list::from_string("");
    list::print(output2, empty);
    EXPECT_EQ(output2.str(), "");
    list::free(empty);
}

TEST(ListTests, Copy) {
    stringstream output1;
    Node* const head1 = list::from_string("test string");
    Node* c_1 = list::copy(head1);
    list::print(output1, c_1);
    EXPECT_EQ(output1.str(), "test string");
    list::free(head1);
    list::free(c_1);

    stringstream output2;
    Node* const head2 = list::from_string("");
    Node* c_2 = list::copy(head2);
    list::print(output2, c_2);
    EXPECT_EQ(output2.str(), "");
    list::free(head2);
    list::free(c_2);
}

TEST(ListTests, CompareFull) {
    Node* const head1 = list::from_string("hello");
    Node* const head2 = list::from_string("hello");
    EXPECT_EQ(list::compare(head1, head2), 0);
    list::free(head2);

    Node* const head3 = list::from_string("testa");
    Node* const head4 = list::from_string("testb");
    EXPECT_LT(list::compare(head3, head4), 0);
    EXPECT_GT(list::compare(head4, head3), 0);
    list::free(head3);
    list::free(head4);

    Node* const head5 = list::from_string("");
    EXPECT_LT(list::compare(head5, head1), 0);
    EXPECT_GT(list::compare(head1, head5), 0);
    list::free(head1);
    list::free(head5);
}

TEST(ListTests, CompareN) {
    Node* const head1 = list::from_string("Hello world");
    Node* const head2 = list::from_string("Hello");
    EXPECT_EQ(list::compare(head1, head2, 5), 0);
    EXPECT_GT(list::compare(head1, head2, 20), 0);
    EXPECT_LT(list::compare(head2, head1, 10), 0);
    list::free(head2);

    Node* const head3 = list::from_string("Hello world");
    EXPECT_EQ(list::compare(head1, head3, 10), 0);
    EXPECT_EQ(list::compare(head3, head1, 100), 0);
    list::free(head3);

    Node* const head4 = list::from_string("");
    EXPECT_LT(list::compare(head4, head1, 10), 0);
    EXPECT_GT(list::compare(head1, head4, 50), 0);
    EXPECT_EQ(list::compare(head1, head4, 0), 0);
    list::free(head1);
    list::free(head4);
}

TEST(ListTests, Reverse) {
    stringstream output1;
    Node* const head1 = list::from_string("abcdefg");
    Node* r_1 = list::reverse(head1);
    list::print(output1, r_1);
    EXPECT_EQ(output1.str(), "gfedcba");
    list::free(head1);
    list::free(r_1);

    stringstream output2;
    Node* const head2 = list::from_string("");
    Node* r_2 = list::reverse(head2);
    list::print(output2, r_2);
    EXPECT_EQ(output2.str(), "");
    list::free(head2);
    list::free(r_2);
}

TEST(ListTests, Append) {
    stringstream output1;
    Node* const head1 = list::from_string("hello ");
    Node* const head2 = list::from_string("world!");
    Node* append_1 = list::append(head1, head2);
    list::print(output1, append_1);
    EXPECT_EQ(output1.str(), "hello world!");
    list::free(head2);
    list::free(append_1);

    stringstream output2, output3, output4;
    Node* const head3 = list::from_string("");
    Node* append_2 = list::append(head1, head3);
    Node* append_3 = list::append(head3, head1);
    Node* append_4 = list::append(head3, head3);
    list::print(output2, append_2);
    list::print(output3, append_3);
    list::print(output4, append_4);

    EXPECT_EQ(output2.str(), "hello ");
    EXPECT_EQ(output3.str(), "hello ");
    EXPECT_EQ(output4.str(), "");
    list::free(head3);
    list::free(head1);
    list::free(append_2);
    list::free(append_3);
    list::free(append_4);
}

TEST(ListTests, Index) {
   Node* const head1 = list::from_string("Hello");
   EXPECT_EQ(list::index(head1, head1), 0);
   list::free(head1);
}

TEST(ListTests, find_char) {
    Node* const head1 = list::from_string("Plin plin plon");
    Node *result1 = list::find_char(head1, 'o'), *result2 = list::find_char(head1, '\0');
    EXPECT_EQ(list::index(head1, result1), 12);
    EXPECT_EQ(list::index(head1, result2), 0);
    list::free(head1);

    Node* const head2 = list::from_string("");
    result1 = list::find_char(head2, 'a');
    EXPECT_EQ(list::index(head2, result1), -1);
}

TEST(ListTests, find_list) {
    Node* head1 = list::from_string("This is a simple string");
    Node* find1 = list::from_string("simple");
    Node* result1 = list::find_list(head1, find1);
    EXPECT_EQ(list::index(head1, result1), 10);
    list::free(find1);

    Node *find2{list::from_string("a")}, *result2{list::find_list(head1, find2)};
    EXPECT_EQ(list::index(head1, result2), 8);
    list::free(find2);

    Node *find3{list::from_string("complex")}, *result3{list::find_list(head1, find3)};
    EXPECT_EQ(list::index(head1, result3), -1);
    list::free(find3);

    Node *find4{list::from_string("")}, *result4{list::find_list(head1, find4)};
    EXPECT_EQ(list::index(head1, result4), 0);
    list::free(find4);
    list::free(head1);

    Node *head2{list::from_string("")}, *find5{list::from_string("foo")}, *result5{list::find_list(head2, find5)};
    EXPECT_EQ(list::index(head2, result5), -1);
    list::free(find5);
    list::free(head2);
}

TEST(ListTests, Nth) {
    Node *head1{list::from_string("Hello")}, *result1{list::nth(head1, 4)};
    EXPECT_EQ(result1->data, 'o');
    Node* result2{list::nth(head1, 0)};
    EXPECT_EQ(result2, head1);
    list::free(head1);
}

TEST(ListTests, Last) {
    Node *head1{list::from_string("Hello")}, *result1{list::last(head1)};
    EXPECT_EQ(result1->data, 'o');
    list::free(head1);
}
