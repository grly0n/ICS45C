#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "compute_grades.hpp"
using namespace std;

TEST(StudentGtests, Validate) {
    Student s1;
    stringstream student1{"Name George Lyon\nQuiz 10 20 30 40 101\nHW 1\nFinal 10"};
    student1 >> s1;
    EXPECT_THROW({s1.validate();}, domain_error);

    Student s2;
    stringstream student2{"Name Joe\nHW -1\nFinal 100"};
    student2 >> s2;
    EXPECT_THROW({s2.validate();}, domain_error);

    Student s3;
    stringstream student3{"Final 150"};
    student3 >> s3;
    EXPECT_THROW({s3.validate();}, domain_error);

    Student s4;
    stringstream student4{"Final 150\nName George L\nHW 10 20 30 40 50 60 70 80\nQuiz 100 100 100 100 100"};
    student4 >> s4;
    EXPECT_THROW({s4.validate();}, domain_error);
}

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

