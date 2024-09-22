#include <iostream>
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

	Node* operator++ () { return next_; } //операция перемещения по узлам списка
	Node* operator= (const Node* rhs) { point_ = rhs->point_; return this; }//операция присваивания для узлов списка
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
	for (Node* tmp = other.first_; tmp != nullptr; tmp++) {// проверить когда присваивается пустой список
		if (tmp->prev_ == nullptr){
			first_ = new Node;
			first_ = tmp;
		} else {
			Node* p = new Node;
			p = tmp;
			p->prev_->next_ = p;
			p = nullptr;
		}
	}
}

Set_points::~Set_points () {
	for (Node* tmp = first_->next_;; tmp++){
		delete tmp->prev_;
		tmp->prev_ = nullptr;
		if (tmp->next_ == nullptr){
			delete tmp;
			break;
		}
	}
}

void Set_points::p_add (double x, double y) {
	Point p(x, y);
	Node* n = new Node;
	n->next_ = first_;
	first_->prev_ = n;
	first_ = n;
	first_->point_ = p;
}






#endif
