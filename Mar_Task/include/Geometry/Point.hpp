#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

<<<<<<< HEAD
static double epsilon = 1e-20;
template <typename T>
static double abs (T x, T y) {
	if (x > y)
=======
static double epsilon = 1e-15;
static double abs (double x, double y) {
	if (x - y >= 0)
>>>>>>> 298e146 (клиент сервер и немного улучшений)
		return x-y;
	return y-x;
}

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}
<<<<<<< HEAD
		bool operator== (Point& other) { return (abs(x, other.x) < epsilon || abs(y, other.y) < epsilon); }
=======
		bool operator== (Point& other) { return (abs(x, other.x) <= epsilon || abs(y, other.y) <= epsilon); }
>>>>>>> 298e146 (клиент сервер и немного улучшений)
		bool operator< (Point& other) { return  ((x < other.x) || (y < other.y)); }
};

#endif
