#include "square.hpp"

Square::Square(Point center, std::string name, int side) :
    Rectangle(center, name, side, side), side(side) {}

Square* Square::clone() const {
    Square* squareCopy = new Square(*this);
    return squareCopy;
}
