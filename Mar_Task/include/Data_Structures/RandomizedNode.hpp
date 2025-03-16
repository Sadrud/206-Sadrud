#ifndef RANDOMIZEDNODE_HPP
#define RANDOMIZEDNODE_HPP

#include <random>
#include "BraidedNode.hpp"

#define N 32767
#define Nd 32767.0

template <class T>
class RandomizedNode : public BraidedNode<T> {
	public:
		RandomizedNode<T> *parent_;
		double priority_;
		void rotateRight ();
		void rotateLeft ();		

	public:
		RandomizedNode (T v, int seed = -1);
		RandomizedNode ();
		RandomizedNode *lchild ();
		RandomizedNode *rchild ();
		RandomizedNode *next ();
		RandomizedNode *prev ();
		RandomizedNode *parent ();
		void lchild (RandomizedNode<T>*);
		void rchild (RandomizedNode<T>*);
		/*void next (RandomizedNode<T>*);
		void prev (RandomizedNode<T>*);
		void parent (RandomizedNode<T>*);*/
		double priority ();
		void priority(double);
		void bubbleUp ();
		void bubbleDown ();
};

template <class T>
RandomizedNode<T>::RandomizedNode (T v, int seed) : BraidedNode<T>(v) {
	if (seed != -1) srand(seed);
	priority_ = (rand() % N)/Nd;
	parent_ = nullptr;
}

template <class T>
RandomizedNode<T>::RandomizedNode () : BraidedNode<T>() {
	srand(-1);
	priority_ = (rand() % N)/Nd;
	parent_ = nullptr;
}

template <class T>
void RandomizedNode<T>::rotateRight () {
	RandomizedNode<T> *y = this;
	RandomizedNode<T> *x = y->lchild();
	RandomizedNode<T> *p = y->parent();
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

template <class T>
void RandomizedNode<T>::rotateLeft () {
	RandomizedNode<T> *x = this;
	RandomizedNode<T> *y = x->rchild();
	RandomizedNode<T> *p = x->parent();
	x->rchild_ = x->lchild();
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
void RandomizedNode<T>::lchild (RandomizedNode<T>* a) { TreeNode<T>::lchild(a); }

template <class T>
void RandomizedNode<T>::rchild (RandomizedNode<T>* a) { TreeNode<T>::rchild(a); }

template <class T>
RandomizedNode<T>* RandomizedNode<T>::parent () { return parent_; }
	
template <class T>
double RandomizedNode<T>::priority () { return priority_; }

template <class T>
void RandomizedNode<T>::priority (double pr) { priority_ = pr; }

#endif
