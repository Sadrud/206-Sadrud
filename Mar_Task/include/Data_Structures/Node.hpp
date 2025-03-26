#ifndef NODE_HPP
#define NODE_HPP

#include "../Exception.hpp"

class Node {
	protected:
		Node* next_;
		Node* prev_;

	public:
		Node () : next_(this), prev_(this) {}
		~Node () {}
		Node* next () { return next_; }
		Node* prev () { return prev_; }
		Node* insert (Node*);
		Node* remove ();
		void splice (Node*);
};

#endif
