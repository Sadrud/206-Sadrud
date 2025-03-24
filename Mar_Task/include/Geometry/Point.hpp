#ifndef POINT_HPP
#define POINT_HPP

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}
};

#endif
