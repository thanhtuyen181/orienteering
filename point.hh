/* point.hh
 *
 * Description:
 * This file defines the Point class, which represents a control
 * point in an orienteering map. Each point has a name,
 * coordinates (x, y), height, and a marker character.
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

#ifndef POINT_HH
#define POINT_HH
#include <string>

using namespace std;

class Point
{
public:
    // Constructor
    Point(string name, int x, int y, int height, char marker);

    // Destructor
   ~Point();

    // Gets the x-coordinate of the point
    int getX() const;

    // Gets the y-coordinate
    int getY() const;

    // Gets the elevation of the point
    int getHeight() const;

    // Gets the marker symbol of the point
    char getMarker() const;

    // Gets the full name of the point
    string getName() const;

private:
    int x_;         // x-coordinate
    int y_;         // y-coordinate
    int height_;    // Elevation
    string name_;   // Name of the point
    char marker_;   // Marker sympol of the point


};
#endif // POINT_HH
