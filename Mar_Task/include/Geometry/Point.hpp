#ifndef POINT_HPP
#define POINT_HPP

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0);
		~Point () {}
}

Point::Point (double x_, double y_) :
	x(x_), y(y_)
{
}

#endif
