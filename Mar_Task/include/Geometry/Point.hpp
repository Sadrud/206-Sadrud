#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}
		bool operator== (Point& other) { return ((x == other.x) || (y == other.y)); }
		bool operator< (Point& other) { return  ((x < other.x) || (y < other.y)); }
};

#endif
