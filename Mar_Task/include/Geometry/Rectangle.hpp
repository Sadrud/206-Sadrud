#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Point.hpp"

class Rectangle {
	public:
		Point sw; 	// bottom left corner
		Point ne;	// upper right corner
		int id;		// identifier
		
		Rectangle () {}
		Rectangle (Point sw_, Point ne_, int id_ = -1) : sw(sw_), ne(ne_), id(id_) {}
		~Rectangle () {}
};

#endif
