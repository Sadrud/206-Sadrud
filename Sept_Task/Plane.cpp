#include "Plane.hpp"

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

#endif
