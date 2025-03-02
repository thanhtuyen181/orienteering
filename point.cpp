/* point.cpp
 *
 * Description:
 * This file implements the Point class, which represents a control
 * point in an orienteering map. The class provides methods to
 * retrieve point attributes like coordinates, height, and
 * marker.
 *
 * Program authors
 *
 * Name: Zannatul Ferdous
 * Student number: 150164676
 * UserID: hczafe
 * E-Mail: zannatul.2.ferdous@tuni.fi
 *
 * Name: Truong Thanh Tuyen
 * Student number: 153156296
 * UserID: hmm638
 * E-Mail: thanhtuyen.truong@tuni.fi
 *
 * */

#include "point.hh"

// Constructs a Point object
Point::Point(string name, int x, int y, int height, char marker): x_(x), y_(y), height_(height)
, name_(name), marker_(marker)
{
}

// Destructor for the Point class
Point::~Point()
{
}

// Return the x-coordinate of the point
int Point::getX() const
{
    return x_;
}

// Return the y-coordinate of the point
int Point::getY() const
{
    return y_;
}

// Return the elevation of the point
int Point::getHeight() const
{
    return height_;
}

// Return the marker character of the point
char Point::getMarker() const
{
    return marker_;
}

// Return the name of the point
string Point::getName() const {
    return name_;
}

