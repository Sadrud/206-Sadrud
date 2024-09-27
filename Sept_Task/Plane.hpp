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


class Set_points {
	Node* first_;

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
	void print_in_rectangle (/*4 прямые*/);

	//дополнительные методы
	bool contains(const Point& point) const;
};

#endif
