#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <random>
#include "List.hpp"

#define N 32767
#define Nd 32767.0

template <class T>
class Dictionary;

template <class T>
class RandomizedNode : public BraidedNode<T> {
	protected:
		RandomizedNode<T> *parent_;
		double priority_;
		void rotateRight ();
		void rotateLeft ();
		void bubbleUp ();
		void bubbleDown ();
		friend class Dictionary<T>;
	public:
		RandomizedNode (T v, int seed = -1);
		RandomizedNode *lchild ();
		RandomizedNode *rchild ();
		RandomizedNode *next ();
		RandomizedNode *prev ();
		RandomizedNode *parent ();
		double priority ();
		void priority(double);
};

template <class T>
RandomizedNode<T>::RandomizedNode (T v, int seed) : BraidedNode<T>(v) {
	if (seed != -1) srand(seed);
	priority_ = (rand() % N)/Nd;
	parent_ = nullptr;
}

template <class T>
void RandomizedNode<T>::rotateRight () {
	if (parent() == nullptr) return;
	RandomizedNode<T> *y = this;
	RandomizedNode<T> *x = y->lchild();
	RandomizedNode<T> *p = y->parent();
	if (x != nullptr) {
		y->lchild_ = x->rchild();
		if (y->lchild() != nullptr)
			y->lchild()->parent_ = y;
		if (p->rchild() == y)
			p->rchild_ = x;
		else
			p->lchild_ = x;
		x->parent_ = p;
		x->rchild_ = y;
		y->parent_ = x;
	}
}

template <class T>
void RandomizedNode<T>::rotateLeft () {
	RandomizedNode<T> *x = this;
	RandomizedNode<T> *y = x->rchild();
	RandomizedNode<T> *p = x->parent();
	if (y != nullptr) {
		x->rchild_ = y->lchild();
		if (x->rchild() != nullptr)
			x->rchild()->parent_ = x;
		if (p->lchild() == x)
			p->lchild_ = y;
		else
			p->rchild_ = y;
		y->parent_ = p;
		y->lchild_ = x;
		x->parent_ = y;
	}
}

template <class T>
void RandomizedNode<T>::bubbleUp () {
	RandomizedNode<T> *p = parent();
	if (priority() < p->priority()) {
		if (p->lchild() == this)
			p->rotateRight();
		else
			p->rotateLeft();
		bubbleUp ();
	}
}

template <class T>
void RandomizedNode<T>::bubbleDown () {
	float lcPriority = lchild() ? lchild()->priority() : 2.0;
	float rcPriority = rchild() ? rchild()->priority() : 2.0;
	float minPriority = (lcPriority < rcPriority) ? lcPriority : rcPriority;
	if (priority() <= minPriority)
		return;
	if (lcPriority < rcPriority)
		rotateRight ();
	else
		rotateLeft ();
	bubbleDown ();
}

template <class T>
RandomizedNode<T>* RandomizedNode<T>::rchild () { return static_cast<RandomizedNode<T>*>(BraidedNode<T>::rchild_); }

template <class T>
RandomizedNode<T>* RandomizedNode<T>::lchild () { return static_cast<RandomizedNode<T>*>(BraidedNode<T>::lchild_); }

template <class T>
RandomizedNode<T>* RandomizedNode<T>::next () { return static_cast<RandomizedNode<T>*>(BraidedNode<T>::next_); }

template <class T>
RandomizedNode<T>* RandomizedNode<T>::prev () { return static_cast<RandomizedNode<T>*>(BraidedNode<T>::prev_); }

template <class T>
RandomizedNode<T>* RandomizedNode<T>::parent () { return parent_; }

template <class T>
double RandomizedNode<T>::priority () { return priority_; }

template <class T>
void RandomizedNode<T>::priority (double pr) { priority_ = pr; }



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
		T first ();
		T last ();
		void inorder (void (*) (T));
		T val ();
		bool isFirst ();
		bool isLast ();
		bool isHead ();
		bool isEmpty ();
		T find (T);
		T findMin ();
		T locate (T);
		T insert (T);
		void remove ();
		T remove (T);
		T removeMin ();
};

template <class T>
Dictionary<T>::Dictionary (int (*c) (T, T), int seed) : cmp_(c){
	root_ = new RandomizedNode<T> (nullptr, seed);
	window_ = root_;
	root_->priority(-1.0);
}

template <class T>
Dictionary<T>::~Dictionary () { 
	while (window_ != root_) {
		last();
		remove();
	}
	delete root_;
}

template <class T>
T Dictionary<T>::first () {
	window_ = root_->next();
	return window_->val_;
}

template <class T>
T Dictionary<T>::last () {
	window_ = root_->prev();
	return window_->val_;
}

template <class T>
T Dictionary<T>::next () {
	window_ = window_->next();
	return window_->val_;
}

template <class T>
T Dictionary<T>::prev () {
	window_ = window_->prev();
	return window_->val_;
}

template <class T>
T Dictionary<T>::val () {
	return window_->val_;
}

template <class T>
void Dictionary<T>::inorder (void (*visit) (T)) {
	RandomizedNode<T>* n = root_->next();
	while (n != root_) {
		(*visit) (n->val_);
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
T Dictionary<T>::find (T val) {
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		int result = (*cmp_) (val, n->val_);
		if (result < 0)
			n = n->lchild();
		else if (result > 0)
			n = n->rchild();
		else {
			window_ = n;
			return n->val_;
		}
	}
	return nullptr;
}

template <class T>
T Dictionary<T>::findMin () {
	window_ = root_->next();
	return window_->val_;
}

template <class T>
T Dictionary<T>::locate (T val) {
	RandomizedNode<T>* b = root_;
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		int result = (*cmp_) (val, n->val_);
		if (result < 0)
			n = n->lchild();
		else if (result > 0) {
			b = n;
			n = n->rchild();
		}
		else {
			window_ = n;
			return window_->val_;
		}
	}
	window_ = b;
	return window_->val_;
}

template <class T>
T Dictionary<T>::insert (T val) {
	int result = 1;
	RandomizedNode<T>* p = root_;
	RandomizedNode<T>* n = root_->rchild();
	while (n) {
		p = n;
		result = (*cmp_) (val, p->val_);
		if (result < 0)
			n = p->lchild();
		else
			n = p->rchild();
	}
	window_ = new RandomizedNode<T>(val);
	window_->parent_ = p;
	if (result < 0){
		p->lchild_ = window_;
		p->prev()->Node::insert(window_);
	}
	else {
		p->rchild_ = window_;
		p->Node::insert(window_);
	}

	window_->bubbleUp();
	return val;
}

template <class T>
void Dictionary<T>::remove_ (RandomizedNode<T>* n) {
	n->priority_ = 1.5;
	n->bubbleDown();
	RandomizedNode<T>* p = n->parent();
	if (p->lchild() == n)
		p->lchild_ = nullptr;
	else
		p->rchild_ = nullptr;
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
T Dictionary<T>::removeMin () {
	T val = root_->next()->val_;
	if (root_ != root_->next())
		remove_(root_->next());
	return val;
}

template <class T>
T Dictionary<T>::remove (T val) {
	T v = find(val);
	if (v) {
		remove();
		return v;
	}
	return nullptr;
}

#endif
