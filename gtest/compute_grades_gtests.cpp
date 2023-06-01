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
    EXPECT_THROW({student1 >> s1;}, domain_error);

    Student s2;
    stringstream student2{"Name Joe\nHW -1\nFinal 100"};
    EXPECT_THROW({student2 >> s2;}, domain_error);

    Student s3;
    stringstream student3{"Final 150"};
    EXPECT_THROW({student3 >> s3;}, domain_error);

    Student s4;
    stringstream student4{"Final 150\nName George L\nHW 10 20 30 40 50 60 70 80\nQuiz 100 100 100 100 100"};
    EXPECT_THROW({student4 >> s4;}, domain_error);
}

