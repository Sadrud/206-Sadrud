#ifndef PLANE_HPP
#define PLANE_HPP

//тип точка плоскости
struct Point {
	double x_, y_;

	Point () {}
	Point (double x, double y) : x_(x), y_(y) {}
	~Point () {}
	Point& operator== (const Point& rhs);
};

struct Node {
	Node *prev_, *next_;
	Point point_;

	Node () : prev_(nullptr), next_(nullptr) {}
	Node (Node* prev, Node* next, Point point) : prev_(prev), next_(next), point_(point) {}
	~Node () { delete [] next_; delete [] prev_; }
};


class Set_points {
	Node* first_;
	Node* last_;

public:
	Set_point ();
	Set_point (const Set_point& other);
	~Set_point ();
	
	Set_points& operator= (const Set_points& rhs);
	bool& operator== (const Set_points& rhs);
	bool& operator!= (const Set_points& rhs);
	friend std::ostream& operator<< (std::ostream& os, const Set_points& list);
	void p_delete (double x, double y);
	void p_add (double (x, double y);
	Set_points& operator| (const Set_points& rhs);
	Set_points& operator& (const Set_points& rhs);
	Set_points& operator- (const Set_points& rhs);
	Set_points& operator|= (const Set_points& rhs);
	Set_points& operator&= (const Set_points& rhs);
	Set_points& operator-= (const Set_points& rhs);
	void print_in_rectangle (/*4 прямые*/);
};


#endif
