/* OrienteeringMap.cpp
 *
 * Description:
 * This file implements the functions for the OrienteeringMap
 * class and the Route struct, managing points and routes for
 * an orienteering map.
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

#include "orienteeringmap.hh"
#include "orienteeringmap.hh"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

// Constructor for OrienteeringMap
// Initalizes an empty map
OrienteeringMap::OrienteeringMap():
    width_(0), height_(0)
{
}

// Destructor for OrienteeringMap
OrienteeringMap::~OrienteeringMap()
{
}

/**
 * @brief Sets the size of the orienteering map.
 *
 * @param width The width of the map.
 * @param height The height of the map.
 */
void OrienteeringMap::set_map_size(int width, int height)
{
    //update map size
    width_ = width;
    height_ = height;
}

/**
 * @brief Adds a control point to the map.
 *
 * @param name Name of the point.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @param height Elevation of the point.
 * @param marker Symbol representing the point on the map.
 */
void OrienteeringMap::add_point(std::string name, int x, int y,
                                int height, char marker)
{
    shared_ptr<Point> new_point = make_shared<Point>(name, x,
                                                     y, height, marker);
    // check if the points already exists
    if(all_points_.find(name) != all_points_.end()){
        all_points_.at(name)->getName();

    }
    //if not , add the point to ur chosen container(s)
    else{
        all_points_.insert({name, new_point});
    }
}

/**
 * @brief Connects two points to form a route.
 *
 * @param from The starting point of the connection.
 * @param to The ending point of the connection.
 * @param route_name The name of the route.
 * @return True if successful, false otherwise.
 */
bool OrienteeringMap::connect_route(std::string from,
                                    std::string to,
                                    std::string route_name)
{
    // check if either of both points exists
    //if not -> return false
    if(all_points_.find(from) == all_points_.end()
            or all_points_.find(to) == all_points_.end()){
        return false;
    }

    //Check if the routes already exists
    //if not -> add the empty route
    if(all_routes_.find(route_name) == all_routes_.end()){
        //create a new route
        all_routes_[route_name] = make_shared<Route>();

        // map[key]= value
        all_routes_[route_name]->name = route_name;

    }

    // Retrieve the route object
    auto& it= all_routes_[route_name];

    // Check if the "from" point is in the route
    vector<shared_ptr<Point>>::iterator iter;
    iter = find(it->point_list.begin(), it->point_list.end(),
                get_point(from));

    // Add "from" point if not present
    if(iter == it->point_list.end()){
          it->point_list.push_back(all_points_[from]);
    }

    // Check if the "to" point is in the route
    iter = find(it->point_list.begin(), it->point_list.end(),
                get_point(to));

    // Add "to" point if not present
    if(iter == it->point_list.end()){
          it->point_list.push_back(all_points_[to]);
    }

    if (from == to) {
        //Error: A point cannot connect to itself
        return false;
    }


    return true;

}

/**
 * @brief Prints the map, displaying all control points.
 */
void OrienteeringMap::print_map() const
{
    std::vector<std::vector<char>> markerVec(height_,
                                             std::vector<char>(width_, '.'));

       // Place the marker characters in the grid
       for (const auto &pair : all_points_) {
           std::shared_ptr<Point> current_point = pair.second;
           int x = current_point->getX() - 1;
           int y = current_point->getY() - 1;

           if (x >= 0 && x < width_ && y >= 0 && y < height_) {
               markerVec[y][x] = current_point->getMarker();
           }
       }

       // Print column headers
       std::cout << " ";  // Leading space for row numbers
       for (int i = 1; i <= width_; ++i) {
           // Every row numbers is put in 3 blank spaces
           std::cout << std::setw(3) << i;
       }
       std::cout << std::endl;

       // Print rows with row headers
       for (int j = 0; j < height_; ++j) {
           std::cout << (j + 1 < 10 ? " " : "") << (j + 1) << "  ";
           for (int k = 0; k < width_; ++k) {
               std::cout << markerVec[j][k] << "  ";
           }
           std::cout << std::endl;
       }
}

/**
 * @brief Prints all available routes.
 */
void OrienteeringMap::print_routes() const
{
    shared_ptr<Route>print_routes = make_shared<Route>();
    //map<string, shared_ptr<Route>>::iterator iter;
    auto iter = all_routes_.begin();
    cout << "Routes:" << endl;
    while(iter!=all_routes_.end()){
        cout << " - " << iter->second->name <<endl;
        ++iter;
    }
}

/**
 * @brief Prints all control points and their markers.
 */
void OrienteeringMap::print_points() const
{
   // map<string, shared_ptr <Point>>::iterator iter;
    cout << "Points: " << endl;
    auto  iter = all_points_.begin();
    while(iter!=all_points_.end()){
        cout << "- " << iter->first <<" : "<< iter->
                second->getMarker()<<endl;
        ++iter;
    }
}

/**
 * @brief Prints all points in a specific route.
 *
 * @param name The name of the route to print.
 */
void OrienteeringMap::print_route(const std::string &name) const
{
    auto it = all_routes_.find(name);
    if (it == all_routes_.end()) {
        std::cout << "Error: Route named " << name
                  << " can't be found" << std::endl;
        return;
    }

    const auto &points = it->second->point_list;

     // Print the first point without arrow
     std::cout << points.front()->getName() << std::endl;

     // Print the remaining points with " -> "
     for (size_t i = 1; i < points.size(); ++i) {
        std::cout << " -> " << points[i]->getName() << std::endl;
     }

}

/**
 * @brief Calculates and prints the length of a specific route.
 *
 * @param name The name of the route.
 */
void OrienteeringMap::route_length(const std::string &name) const
{
    // Check if the route exists in the map
    auto it = all_routes_.find(name);
    if (it == all_routes_.end()) {
        std::cout << "Error: Route named " << name
                  << " can't be found" << std::endl;
        return;
    }

    // Calculate the route length using the calculate_length()
    double length = it->second->calculate_length();

    // Print the length of route with 2 decimal precision
    std::cout << std::setprecision(2) << "Route " << name
              << " length was " << length << std::endl;
}

/**
 * @brief Finds and prints the greatest continuous rise
 * from a point.
 *
 * @param point_name The starting point.
 */
void OrienteeringMap::greatest_rise(const std::string &point_name) const {
    // Find the point in the map
    auto point_it = all_points_.find(point_name);
    if (point_it == all_points_.end()) {
        std::cout << "Error: Point named " << point_name
                  << " can't be found" << std::endl;
        return;
    }

    std::shared_ptr<Point> start_point = point_it->second;
    int max_rise = 0;
    std::vector<std::string> max_routes;

    // Iterate through all routes to find the greatest rise from
    // the point
    for (const auto &route_pair : all_routes_) {
        int rise = route_pair.second->greatest_rise_from_point(start_point);
        if (rise > max_rise) {
            max_rise = rise;

            // Reset and store only this route
            max_routes = {route_pair.first};

        } else if (rise == max_rise && rise > 0) {
            // Store additional route with the same max rise
            max_routes.push_back(route_pair.first);
        }
    }

    // Print the results
    if (max_rise == 0) {
        std::cout << "No route rises after point "
                    << point_name << std::endl;
    } else {
        std::cout << "Greatest rise after point " << point_name
                  << ", " << max_rise << " meters, is on route(s):"
                  << std::endl;

        for (const auto &route : max_routes) {
            std::cout << " - " << route << std::endl;
        }
    }
}

/**
 * @brief Retrieves a point from the map by its name.
 *
 * @param name The name of the point to retrieve.
 *
 * @return A shared pointer to the Point if found,
 * otherwise nullptr.
 */
shared_ptr<Point> OrienteeringMap::get_point(string name) const
{
     auto it = all_points_.find(name);
     if(it != all_points_.end()){
         return it->second;// Return the existing point
     }
        return nullptr; // Point not found
}

/**
 * @brief Calculates the total length of the route.
 *
 * The length is computed as the sum of the Euclidean distances
 * between consecutive points in the route.
 *
 * @return total_length The total length of the route as a double.
 */
double Route::calculate_length() const {
    // A route with fewer than 2 points has no length
    if (point_list.size() < 2) return 0.0;

    double total_length = 0.0;

    // Iterate through each consecutive pair of points to compute
    // the total distance
    for (size_t i = 1; i < point_list.size(); ++i) {
        int dx = point_list[i]->getX() - point_list[i - 1]->getX();
        int dy = point_list[i]->getY() - point_list[i - 1]->getY();

        // Using the Euclidean distance formula
        total_length += std::sqrt(dx * dx + dy * dy);
    }
    return total_length;
}

/**
 * @brief Finds the greatest continuous rise from a given point.
 *
 * The function calculates the longest sequence of height increases,
 * stopping when a decline occurs.
 *
 * @param start_point The point from which to begin the rise calculation.
 *
 * @return max_rise The maximum continuous rise in elevation.
 */
int Route::greatest_rise_from_point(shared_ptr<Point> start_point) const {
    // Find the starting point in the route
    auto it = std::find(point_list.begin(), point_list.end(),
                        start_point);
    if (it == point_list.end()) {
        return 0;  // The point is not in this route
    }

    int max_rise = 0;
    int current_rise = 0;

    // Get the height of the starting point
    int prev_height = (*it)->getHeight();

    // Iterate from the starting point to the end of the route
    for (++it; it != point_list.end(); ++it) {
        int height = (*it)->getHeight();

        // Continue counting if rising or flat
        if (height >= prev_height) {
            current_rise += (height - prev_height);

        // else stop counting the rise if there is a decline
        } else {
            break;
        }

        prev_height = height;
        max_rise = std::max(max_rise, current_rise);
    }
    return max_rise;
}


