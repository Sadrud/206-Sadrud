#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

static double eps = 1e-15;
static double abs (double x, double y) {
	if (x - y >= 0)
		return x-y;
	return y-x;
}

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}
		bool operator== (Point& other) { return (abs(x, other.x) <= eps || abs(y, other.y) <= eps); }
		bool operator< (Point& other) { return  ((x < other.x) || (y < other.y)); }
};

#endif
