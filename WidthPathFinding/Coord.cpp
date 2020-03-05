#include "Coord.h"

Coord::Coord(int x, int y) {
	this->x = x;
	this->y = y;
}
Coord::~Coord() {}

void Coord::operator+=(const Coord& other) {
	this->x += other.x;
	this->y += other.y;
}

bool Coord::operator==(const Coord& other) const {
	return this->x == other.x && this->y == other.y;
}

bool Coord::operator!=(const Coord& other) const {
	return this->x != other.x || this->y != other.y;
}

Coord Coord::operator+(const Coord& other) const {
	Coord temp;

	temp.x = this->x + other.x;
	temp.y = this->y + other.y;

	return temp;
}
