#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
class Edge {
	private:
		Point org;
		Point dest;
	
	public:
		Edge (Point& org_, Point& dest_) : org(org_), dest(dest_) {}
		Edge () : org(Point(0, 0)), dest(Point(1, 0)) {}
		~Edge () {}
		void print () { std::cout << "Edge: (" << org.x << ", " << org.y << ") -> (" << dest.x << ", " << dest.y << ")" << std::endl; }
};

#endif
