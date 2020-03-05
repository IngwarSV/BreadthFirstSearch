#pragma once

#include "Specifications.h"

class Coord {
public:
    int x;
    int y;

    Coord(int x = WIDTH / 2, int y = HEIGHT / 2);
    ~Coord();

    void operator+=(const Coord& other);
    bool operator==(const Coord& other) const;
    bool operator!=(const Coord& other) const;
    Coord operator+(const Coord& other) const;
};
