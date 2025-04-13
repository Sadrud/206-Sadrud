#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

static double epsilon = 1e-20;
template <typename T>
static double abs (T x, T y) {
	if (x > y)
		return x-y;
	return y-x;
}

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}
		bool operator== (Point& other) { return (abs(x, other.x) <= epsilon || abs(y, other.y) <= epsilon); }
		bool operator< (Point& other) { return  ((x < other.x) || (y < other.y)); }
		//double x() { return x; }
		//double y() { return y; }
};

#endif
