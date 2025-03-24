#ifndef BRAIDEDNODE_HPP
#define BRAIDEDNODE_HPP

#include "Node.hpp"
#include "TreeNode.hpp"

template <typename T>
class BraidedNode : public Node, public TreeNode<T> {
	public:
		BraidedNode (T);
		BraidedNode<T>* rchild ();
		BraidedNode<T>* lchild ();
		BraidedNode<T>* next ();
		BraidedNode<T>* prev ();
};

template <typename T>
BraidedNode<T>::BraidedNode (T val) : Node (), TreeNode<T>(val) {}

template <typename T>
BraidedNode<T>* BraidedNode<T>::rchild () { return static_cast<BraidedNode<T>*>(TreeNode<T>::rchild_); }

template <typename T>
BraidedNode<T>* BraidedNode<T>::lchild () { return static_cast<BraidedNode<T>*>(TreeNode<T>::lchild_); }

template <typename T>
BraidedNode<T>* BraidedNode<T>::next () { return static_cast<BraidedNode<T>*>(Node::next_); }

template <typename T>
BraidedNode<T>* BraidedNode<T>::prev () { return static_cast<BraidedNode<T>*>(Node::prev_); }

#endif
