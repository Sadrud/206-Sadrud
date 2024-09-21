#include <iostream>
#ifndef PLANE_HPP
#define PLANE_HPP

//тип точка плоскости
struct Point {
	double x_, y_;

	Point () {}
	Point (double x, double y) : x_(x), y_(y) {}
	~Point () {}
	bool operator== (const Point& rhs) {if (x_ == rhs.x_ && y_ == rhs.y_) return true; return false; }
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
	Set_points ();
	Set_points (const Set_points& other);
	~Set_points ();
	
	Set_points& operator= (const Set_points& rhs);
	bool& operator== (const Set_points& rhs);
	bool& operator!= (const Set_points& rhs);
	friend std::ostream& operator<< (std::ostream& os, const Set_points& list);
	void p_delete (double x, double y);
	void p_add (double x, double y);
	Set_points& operator| (const Set_points& rhs);
	Set_points& operator& (const Set_points& rhs);
	Set_points& operator- (const Set_points& rhs);
	Set_points& operator|= (const Set_points& rhs);
	Set_points& operator&= (const Set_points& rhs);
	Set_points& operator-= (const Set_points& rhs);
	void print_in_rectangle (/*4 прямые*/) {}
};


#endif
