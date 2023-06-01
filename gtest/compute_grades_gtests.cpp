#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "compute_grades.hpp"
using namespace std;

TEST(StudentGtests, Output) {
    Student s1;
    stringstream student1{"Name Hello World\nQuiz 10 20 30\nHW 10 20 30\nFinal 100"};
    stringstream output1;
    student1 >> s1;
    s1.compute_grade();
    output1 << s1;
    EXPECT_EQ(output1.str(), std::string("Name:   Hello World\nHW Ave: 20\nQZ Ave: 25\nFinal:  100\nTotal:  46\nGrade:  F\n"));

    Student s2;
    stringstream student2{"Name Hello World Foo\nQuiz 0\nFinal 0"};
    stringstream output2;
    student2 >> s2;
    s2.compute_grade();
    output2 << s2;
    EXPECT_EQ(output2.str(), std::string("Name:   Hello World Foo\nHW Ave: 0\nQZ Ave: 0\nFinal:  0\nTotal:  0\nGrade:  F\n"));
}

