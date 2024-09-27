#include "Plane.hpp"
#include <cmath>

#ifndef PLANE_CPP
#define PLANE_CPP

//конструктор копирования
Set_points::Set_points (const Set_points& other) {
	for (Node* tmp = other.first_; tmp != nullptr; tmp = tmp->next_) {
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

//деструктор
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

//добавление одной точки в множество
void Set_points::p_add (double x, double y) {
	Point p(x, y);
	for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_) { if (ptr->point_.x_ == x && ptr->point_.y_ == y) throw Exception (1, "Добавление элемента. Элемент уже есть в множестве."); }

	Node* n = new Node;
	if (first_ == nullptr) { first_ = n; }
	else {
		n->next_ = first_;
		first_->prev_ = n;
		first_ = n;
	}
	first_->point_ = p;
}


//печать множества точек
std::ostream& operator<< (std::ostream& os, const Set_points& set) {
	if (set.first_ == nullptr) { os << "Печать множества. Множество пусто." << std::endl; return os; }

	for (Node* ptr = set.first_; ptr != nullptr; ptr = ptr->next_) { os << "(" << ptr->point_.x_ << "," << ptr->point_.y_ << ")" << " "; }
	os << std::endl;
	return os;
}


//удаление точки из множества
void Set_points::p_delete (double x, double y) {
	if (first_ == nullptr) { throw Exception (3, "Удаление элемента. Множество пусто."); }
	for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_) { 
		if (ptr->point_.x_ == x && ptr->point_.y_ == y) {
			if (ptr->prev_ == nullptr && ptr->next_ == nullptr) { delete ptr; first_ = nullptr; break; }
			if (ptr->prev_ == nullptr) { ptr->next_->prev_ = nullptr; first_ = ptr->next_; delete ptr; break; }
			if (ptr->next_ == nullptr) { ptr->prev_->next_ = nullptr; delete ptr; break; }
			ptr->prev_->next_ = ptr->next_;
			ptr->next_->prev_ = ptr->prev_;
			delete ptr;
			break; 
		}
		if (ptr->next_ == nullptr)
			throw Exception (2, "Удаление элемента. Элемента нет в множестве."); 
	}
}


//оператор присваивание
Set_points& Set_points::operator= (const Set_points& rhs) {
	if (this != &rhs) {
		for (Node* ptr = first_; ptr != nullptr; ptr = first_) { p_delete(ptr->point_.x_, ptr->point_.y_); }

		for (Node* tmp = rhs.first_; tmp != nullptr; tmp = tmp->next_) {
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
	return *this;
}


//операторы сравнения
bool Set_points::operator== (const Set_points& rhs) const {
	if (first_ == nullptr && rhs.first_ == nullptr)
		return true;

	if (first_ == nullptr || rhs.first_ == nullptr)
		return false;

	int k = 0, p = 0;
	for (Node *n = first_; n != nullptr ; n = n->next_) { k++; }
	for (Node *m = rhs.first_; m != nullptr ; m = m->next_) { p++; }
	if (k != p) { return false; }

	for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_) {
		for (Node* tmp = rhs.first_; tmp != nullptr; tmp = tmp->next_) {
			if (tmp->point_.x_ == ptr->point_.x_ && tmp->point_.y_ == ptr->point_.y_) 
				break;
			if (tmp->next_ == nullptr)
				return false;
		}
	}
	return true;
}

bool Set_points::operator!= (const Set_points& rhs) const { return !(*this == rhs); }

//проверка на содержание элемента в множестве
bool Set_points::contains(const Point& point) const {
	for (Node* current = first_; current != nullptr; current = current->next_) {
		if (current->point_.x_ == point.x_ && current->point_.y_ == point.y_) {
			return true;
		}
	}
	return false;
}


//объединение множеств
Set_points Set_points::operator| (const Set_points& rhs) {
	if (*this == rhs) { return *this; }

	Set_points result;

	if (first_ == nullptr) {
		for (Node* current = rhs.first_; current != nullptr; current = current->next_) {
			result.p_add(current->point_.x_, current->point_.y_);
		}
		return result;
	}

	if (rhs.first_ == nullptr) { return *this; }

	for (Node* current = first_; current != nullptr; current = current->next_) {
		result.p_add(current->point_.x_, current->point_.y_);
	}

	for (Node* current = rhs.first_; current != nullptr; current = current->next_) {
		if (!this->contains(current->point_)) { result.p_add(current->point_.x_, current->point_.y_); }
	}
	return result;
}


//пересечение множеств
Set_points Set_points::operator& (const Set_points& rhs) {
	Set_points result;
	if (first_ == nullptr || rhs.first_ == nullptr) { return result; }

	for (Node* current = this->first_; current != nullptr; current = current->next_) {
		if (rhs.contains(current->point_)) { result.p_add(current->point_.x_, current->point_.y_); }
	}
	return result;
}


//разность множеств
Set_points Set_points::operator- (const Set_points& rhs) {
	Set_points result;
	if (*this == rhs) { return Set_points(); } //почему если поставить return result происходит Segmentation fault

	if (this->first_ == nullptr) { return result; }
	
	if (rhs.first_ == nullptr) { return *this; }

	for (Node* current = this->first_; current != nullptr; current = current->next_) {
		if (!rhs.contains(current->point_)) { result.p_add(current->point_.x_, current->point_.y_); }
	}
	return result;
}


Set_points Set_points::operator|= (const Set_points& rhs) { return *this = (*this|rhs); }
Set_points Set_points::operator&= (const Set_points& rhs) { return *this = (*this&rhs); }
Set_points Set_points::operator-= (const Set_points& rhs) { return *this = (*this-rhs); }


//отступление...
//класс Rectangle

//расстояние между точками
double Rectangle::distance (const Point& p1, const Point& p2) const { return std::sqrt((p1.x_ - p2.x_)*(p1.x_ - p2.x_) + (p1.y_ - p2.y_)*(p1.y_ - p2.y_)); }

//скалярное произведениедвух векторов
double Rectangle::scalar_product (const Point& p1, const Point& p2, const Point& p3, const Point& p4) const { return ((p2.x_ - p1.x_)*(p4.x_ - p3.x_) + (p2.y_ - p1.y_)*(p4.y_ - p3.y_)); }

//векторное произведение (ориентированная (+/-) площадь между двумя векторами)
double Rectangle::cross_product (const Point& p1, const Point& p2, const Point& p3, const Point& p4) const { return ((p2.x_ - p1.x_)*(p4.y_ - p3.y_) - (p4.x_ - p3.x_)*(p2.y_ - p1.y_)); }

//проверка на прямоугольник
bool Rectangle::is_rectangle () const {
	if (scalar_product(p1_, p2_, p1_, p3_) == 0 && scalar_product(p4_, p2_, p4_, p3_) == 0) {
		if (distance(p1_, p2_) == distance(p3_, p4_) && distance(p1_, p3_) == distance(p2_, p4_)) return true;
	}
	if (scalar_product(p1_, p2_, p1_, p3_) != 0) {
		if (scalar_product(p1_, p2_, p1_, p4_) == 0 && scalar_product(p3_, p2_, p3_, p4_) == 0) {
			if (scalar_product(p1_, p2_, p1_, p4_) == 0 && scalar_product(p3_, p2_, p3_, p4_) == 0) return true;
		}
	}
	if (scalar_product(p1_, p2_, p1_, p3_) != 0 && scalar_product(p1_, p2_, p1_, p4_) != 0) {
		if (scalar_product(p1_, p3_, p1_, p4_) == 0 && scalar_product(p2_, p3_, p2_, p4_) != 0) {
			if (distance(p1_, p3_) == distance(p2_, p4_) && distance(p2_, p3_) == distance(p1_, p4_)) return true;
		}
	}
	return false;
}

double Rectangle::max_distance () {
	if ((distance(p1_, p2_) > distance(p1_, p3_)) && (distance(p1_, p2_) > distance(p1_, p4_))) { return distance(p1_, p2_); }
	if ((distance(p1_, p3_) > distance(p1_, p2_)) && (distance(p1_, p3_) > distance(p1_, p4_))) { return distance(p1_, p3_); }
	return distance(p1_, p4_);;
}

void Rectangle::order () {
	Point t = p1_;
	if (distance(p1_, p2_) == max_distance ()) { t = p2_; p2_ = p3_; p3_ = t; }
	if (distance(p2_, p3_) == max_distance ()) { t = p3_; p3_ = p4_; p4_ = t; }
}

//наличие точки в прямоугольнике
bool Rectangle::is_point_in_rectangle(const Point& point){
	if (!is_rectangle()) { throw Exception (4, "Это не прямоугольник."); }
	this->order();

	double cross1 = cross_product(point, p1_, point, p2_);
	double cross2 = cross_product(point, p2_, point, p3_);
	double cross3 = cross_product(point, p3_, point, p4_);
	double cross4 = cross_product(point, p4_, point, p1_);

	return (cross1 > 0 && cross2 > 0 && cross3 > 0 && cross4 > 0) || (cross1 < 0 && cross2 < 0 && cross3 < 0 && cross4 < 0);
}

//опять множество точек
// вывод точек находящихся внутри прямоугольника
void Set_points::print_in_rectangle(Rectangle& rect) {
	for (Node* ptr = first_; ptr != nullptr; ptr = ptr->next_){
		if (rect.is_point_in_rectangle(ptr->point_))
			std::cout << "(" << ptr->point_.x_ << "," << ptr->point_.y_ << ") ";
	}
	std::cout << std::endl;
} 

#endif
