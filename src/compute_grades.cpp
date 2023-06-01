#include <algorithm>
#include <numeric>
#include <cmath>
#include <compare>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "compute_grades.hpp"

std::vector<std::string> load_stream(std::istream& in) {
    std::string line;
    std::stringstream data;
    std::vector<std::string> output;
    while (getline(in, line)) {
        if(!line.size()) {
            output.push_back(data.str());
            data.str(std::string());
        } else data << line << '\n';
    }
    return output;
}


//Student validate
void Student::validate() const {
    auto check = [](int x){if (x < 0 || x > 100) throw std::domain_error("Error: invalid percentage " + x);};
    std::for_each(begin(quiz), end(quiz), check);
    std::for_each(begin(hw), end(hw), check);
    if (final_score < 0 || final_score > 100) throw std::domain_error("Error: invalid percentage " + std::to_string(final_score));
}


//Student extractor
std::istream& operator>>(std::istream& in, Student& s) {
    std::string line;
    std::vector<std::string> data;
    while(getline(in, line)) {data.push_back(line);}

    std::vector<std::string> kwds {"Name", "Quiz", "HW", "Final"};
    
    std::for_each(begin(data), end(data), [&](std::string line){
        std::stringstream stream(line); std::string keyword;
        stream >> keyword;
        if (std::find(begin(kwds), end(kwds), keyword) != end(kwds)) {
            if (keyword == std::string("Name")) {
                stream >> s.first_name;
                if (!stream.eof()) s.last_name = std::string();
                std::for_each(std::istream_iterator<std::string>(stream), {}, 
                    [&](std::string str){s.last_name += ' ' + str;});
            }
            else if (keyword == std::string("Quiz")) {
                std::for_each(std::istream_iterator<std::string>(stream), {},
                    [&](std::string str){s.quiz.push_back(std::stoi(str));});
            }
            else if (keyword == std::string("HW")) {
                std::for_each(std::istream_iterator<std::string>(stream), {},
                    [&](std::string str){s.hw.push_back(std::stoi(str));});
            }
            else if (keyword == std::string("Final")) {
                std::string string_final;
                stream >> string_final;
                s.final_score = std::stod(string_final);
            }
        }
    });
    return in;
}


//Student inserter
std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name: " << s.first_name << s.last_name << '\n' <<
           std::setw(8) << "HW Ave: " << s.hw_avg << '\n' <<
           std::setw(8) << "QZ Ave: " << s.quiz_avg << '\n' <<
           std::setw(8) << "Final: " << s.final_score << '\n' <<
           std::setw(8) << "Total: " << s.course_score << '\n' <<
           std::setw(8) << "Grade: " << s.course_grade << std::endl;
    return out;
}


//Compute average quiz
void Student::compute_quiz_avg() {
    if (!quiz.size()) quiz_avg = 0;
    else if (quiz.size() == 1) quiz_avg = quiz[0];
    else {
        std::vector<int> adjustedQuiz(quiz);
        std::sort(begin(adjustedQuiz), end(adjustedQuiz));
        adjustedQuiz.erase(begin(adjustedQuiz), begin(adjustedQuiz)+1);
        quiz_avg = std::accumulate(begin(adjustedQuiz), end(adjustedQuiz), 0.0) / adjustedQuiz.size() + 0.0;
   }
}


//Compute average hw
void Student::compute_hw_avg() {
    if (!hw.size()) hw_avg = 0;
    else hw_avg = std::accumulate(begin(hw), end(hw), 0.0) / hw.size() + 0.0;
}


//Compute course score
void Student::compute_course_score() {
    course_score = std::round(0.4 * quiz_avg + 0.3 * hw_avg + 0.3 * final_score);
}


//Compute letter grade
void Student::compute_grade() {
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    
    if (97 <= course_score) course_grade = "A+";
    else if (93 <= course_score) course_grade = "A";
    else if (90 <= course_score) course_grade = "A-";
    else if (87 <= course_score) course_grade = "B+";
    else if (83 <= course_score) course_grade = "B";
    else if (80 <= course_score) course_grade = "B-";
    else if (77 <= course_score) course_grade = "C+";
    else if (73 <= course_score) course_grade = "C";
    else if (70 <= course_score) course_grade = "C-";
    else if (67 <= course_score) course_grade = "D+";
    else if (63 <= course_score) course_grade = "D";
    else if (60 <= course_score) course_grade = "D-";
    else course_grade = "F";
}


//Student spaceship operator
std::strong_ordering Student::operator<=>(const Student& other) const {
    std::strong_ordering last_name_compare = last_name.compare(other.last_name) <=> 0;
    if (last_name_compare != 0) return last_name_compare;
    else return first_name.compare(other.first_name) <=> 0;
}


//Student comparison operator
bool Student::operator==(const Student& other) const {
    return (last_name == other.last_name && first_name == other.first_name);
}


//Gradebook compute grades
void Gradebook::compute_grades() {
    std::for_each(begin(students), end(students), [](Student& s){s.compute_grade();});
}


//Gradebook validate
void Gradebook::validate() const {
    std::for_each(begin(students), end(students), [](const Student& s){s.validate();});
}


//Gradebook sort
void Gradebook::sort() {
    std::sort(begin(students), end(students));
}

//Gradebook extractor
std::istream& operator>>(std::istream& in, Gradebook& b) {
    std::vector<std::string> data {load_stream(in)};

    std::for_each(begin(data), end(data), [&](std::string str){
        std::stringstream stream;
        stream << str;
        Student s;
        stream >> s;
        b.students.push_back(s);});

    return in;
}


//Gradebook inserter
std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    std::for_each(begin(b.students), end(b.students), [&](Student s){out << s;});
    return out;
}
