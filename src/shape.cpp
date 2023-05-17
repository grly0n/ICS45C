#include "shape.hpp"
#include <iostream>
using namespace std;

Shape::Shape(Point center, string name) : center(center), name(name) {}

void Shape::print(ostream& out) const {
    out << name << "(" << center.x << ", " << center.y << ")\n";
}
