#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Point.hpp"

class Rectangle {
	public:
		Point sw; 	// bottom left corner
		Point ne;	// upper right corner
		int id;		// identifier
		
		Rectangle (Point &sw_, Point &ne_, int id_ = -1);
		Rectangle (void) {}
		~Rectangle () {}
};

Rectangle::Rectangle (Point &sw_, Point &ne_, int &id_):
	sw(sw_), ne(ne_), id(id_)
{
}

#endif
