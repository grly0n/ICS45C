#include <cmath>
#include <iostream>
#include <numbers>
#include <string>

#include "array.hpp"
#include "matrix.hpp"

using namespace std;

int main() {
    Matrix<string> mat{2,3};
    cin >> mat;
    cout << mat << endl;
}
