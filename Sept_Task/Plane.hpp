#include "Exception.hpp"
#ifndef PLANE_HPP
#define PLANE_HPP

//тип точка плоскости
struct Point {
	double x_, y_;

	Point () {}
	Point (double x, double y) : x_(x), y_(y) {}
	Point (const Point& rhs) { x_ = rhs.x_; y_ = rhs.y_; }
	~Point () {}
	bool operator== (const Point& rhs) {if (x_ == rhs.x_ && y_ == rhs.y_) return true; return false; }
	Point& operator= (const Point& rhs) {if (this != &rhs) { x_ = rhs.x_; y_ = rhs.y_; } return *this; }
};

/*
 * РЕАЛИЗАЦИЯ МНОЖЕСТВА ТОЧЕК ПЛАНИРУЕТСЯ В ВИДЕ ДВУНАПРАВЛЕННОГО (ПОЧТИ) СПИСКА
 * ТАК КАК УДАЛЕНИЕ И ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ ЗДЕСЬ БУДЕТ БЫСТРЕЕ, ЧЕМ В МАССИВЕ
 */
struct Node {
	Node *prev_, *next_;
	Point point_;

	Node () : prev_(nullptr), next_(nullptr) {}
	Node (Node* prev, Node* next, Point point) : prev_(prev), next_(next), point_(point) {}
};

//класс прямоугольник, чтобы опрделять точки внутри прмоугольника
class Rectangle {
	Point p1_, p2_, p3_, p4_;

	public:
	Rectangle (Point p1, Point p2, Point p3, Point p4) : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {}
	~Rectangle () {}

	bool is_rectangle () const;
	bool is_point_in_rectangle(const Point& point);

	//дополнительные методы
	double distance (const Point& p1, const Point& p2) const;
	double scalar_product (const Point& p1, const Point& p2, const Point& p3, const Point& p4) const;
	double cross_product (const Point& p1, const Point& p2, const Point& p3, const Point& p4) const;
	double max_distance ();
	void order ();
};

class Set_points {
	Node* first_;
	friend class Rectangle;

	public:
	Set_points () { first_ = nullptr; }
	Set_points (const Set_points& other);
	~Set_points ();

	Set_points& operator= (const Set_points& rhs);
	bool operator== (const Set_points& rhs) const;
	bool operator!= (const Set_points& rhs) const;
	friend std::ostream& operator<< (std::ostream& os, const Set_points& list);
	void p_delete (double x, double y);
	void p_add (double x, double y);
	Set_points operator| (const Set_points& rhs);
	Set_points operator& (const Set_points& rhs);
	Set_points operator- (const Set_points& rhs);
	Set_points operator|= (const Set_points& rhs);
	Set_points operator&= (const Set_points& rhs);
	Set_points operator-= (const Set_points& rhs);
	void print_in_rectangle (Rectangle& rect);

	//дополнительные методы
	bool contains(const Point& point) const;
};

#endif
