#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <optional>
#include "RandomizedNode.hpp"
#include "../Exception.hpp"

template <typename T>
class Dictionary {
	private:
		RandomizedNode<T>* root_;
		RandomizedNode<T>* window_;
		int (*cmp_) (T, T);
		void remove_ (RandomizedNode<T>*);

	public:
		Dictionary (int (*) (T, T), int = -1);
		~Dictionary ();
		T next ();
		T prev ();
		void inorder (void (*) (T));
		T val ();
		bool isFirst ();
		bool isLast ();
		bool isHead ();
		bool isEmpty ();
		bool find (T);
		T findMin ();
		T locate (T);
		void insert (T);
		void remove ();
		void remove (T);
		void removeMin ();
};

template <class T>
Dictionary<T>::Dictionary (int (*c) (T, T), int seed) : cmp_(c){
	root_ = new RandomizedNode<T> (seed);
	window_ = root_;
	root_->priority(-1.0);
}

template <class T>
Dictionary<T>::~Dictionary () { delete root_; }

template <class T>
T Dictionary<T>::next () {
	window_ = window_->next();
	return static_cast<T>(window_->val());
}

template <class T>
T Dictionary<T>::prev () {
	window_ = window_->prev();
	return window_->val();
}

template <class T>
T Dictionary<T>::val () {
	return window_->val();
}

template <class T>
void Dictionary<T>::inorder (void (*visit) (T)) {
	RandomizedNode<T>* n = root_->next();
	while (n != root_) {
		(*visit) (n->val);
		n = n->next();
	}
}

template <class T>
bool Dictionary<T>::isFirst () {
	return (window_ == root_->next()) && (root_ != root_->next());
}

template <class T>
bool Dictionary<T>::isLast () {
	return (window_ == root_->prev()) && (root_ != root_->next());
}

template <class T>
bool Dictionary<T>::isHead () {
	return (window_ == root_);
}

template <class T>
bool Dictionary<T>::isEmpty () {
	return root_ == root_->next();
}

template <class T>
bool Dictionary<T>::find (T val) {
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		int result = (*cmp_) (val, n->val());
		if (result < 0)
			n = n->lchild();
		else if (result > 0)
			n = n->rchild();
		else {
			window_ = n;
			return true;
		}
	}
	return false;
}

template <class T>
T Dictionary<T>::findMin () {
	window_ = root_->next();
	return window_->val();
}

template <class T>
T Dictionary<T>::locate (T val) {
	RandomizedNode<T>* b = root_;
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		int result = (*cmp_) (val, n->val());
		if (result < 0)
			n = n->lchild();
		else if (result > 0) {
			b = n;
			n = n->rchild();
		}
		else {
			window_ = n;
			return window_->val();
		}
	}
	window_ = b;
	return window_->val();
}

template <class T>
void Dictionary<T>::insert (T val) {
	int result = 1;
	RandomizedNode<T>* p = root_;
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		p = n;
		result = (*cmp_) (val, p->val());
		if (result < 0)
			n = p->lchild();
		else if (result > 0) 
			n = p->rchild();
		else
			return;
	}
	window_ = new RandomizedNode<T>(val);
	window_->parent_ = p;
	if (result < 0){
		p->lchild(window_);
		p->prev()->Node::insert(window_);
	}
	else {
		p->rchild(window_);
		p->Node::insert(window_);
	}

	window_->bubbleUp();
}

template <class T>
void Dictionary<T>::remove_ (RandomizedNode<T>* n) {
	n->priority_ = 1.5;
	n->bubbleDown();
	RandomizedNode<T>* p = n->parent();
	if (p->lchild() == n)
		p->TreeNode<T>::lchild(nullptr);
	else
		p->TreeNode<T>::rchild(nullptr);
	if (window_ == n)
		window_ = n->prev();
	n->Node::remove();
	delete n;
}

template <class T>
void Dictionary<T>::remove () {
	if (window_ != root_)
		remove_(window_);
}

template <class T>
void Dictionary<T>::removeMin () {
	T val = root_->next()->val;
	if (root_ != root_->next())
		remove_(root_->next());
}

template <class T>
void Dictionary<T>::remove (T val) {
	bool v = find(val);
	if (!v) throw Exception (1, "Значение отстутствует.");
	remove ();
}

#endif
