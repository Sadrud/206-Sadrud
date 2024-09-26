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
	bool operator== (const Set_points& rhs);
	bool operator!= (const Set_points& rhs);
	friend std::ostream& operator<< (std::ostream& os, const Set_points& list);
	void p_delete (double x, double y);
	void p_add (double x, double y);
	Set_points& operator| (const Set_points& rhs);
	Set_points& operator& (const Set_points& rhs);
	Set_points& operator- (const Set_points& rhs);
	Set_points& operator|= (const Set_points& rhs);
	Set_points& operator&= (const Set_points& rhs);
	Set_points& operator-= (const Set_points& rhs);
	void print_in_rectangle (/*4 прямые*/);
};





Set_points::Set_points (const Set_points& other) {
	for (Node* tmp = other.first_; tmp != nullptr; tmp = tmp->next_) {// проверить когда присваивается пустой список
		if (tmp->prev_ == nullptr){
			first_ = new Node;
			first_->point_ = tmp->point_;
		} else {
			Node* p = new Node;
			p->point_ = tmp->point_;
			for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_) { p->prev_ = ptr; }
			p->prev_->next_ = p;
		}
	}
}

Set_points::~Set_points () {
	if (first_ != nullptr){
		if (first_->next_ == nullptr)
			delete first_;
		else {
			for (Node* tmp = first_->next_; tmp != nullptr; tmp = tmp->next_){
				delete tmp->prev_;
				first_ = tmp;
			}
			delete first_;
		}
	}
}

void Set_points::p_add (double x, double y) {
	Point p(x, y);
	for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_) { if (ptr->point_.x_ == x && ptr->point_.y_ == y) throw Exception (1, "Элемент уже есть в множествке."); }

	Node* n = new Node;
	if (first_ == nullptr) { first_ = n; }
	else {
		n->next_ = first_;
		first_->prev_ = n;
		first_ = n;
	}
	first_->point_ = p;
}




#endif
