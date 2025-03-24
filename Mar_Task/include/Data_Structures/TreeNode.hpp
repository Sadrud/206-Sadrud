#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <type_traits>

template <class T>
class TreeNode {
	static_assert(std::is_pointer<T>::value, "Template parameter must be a pointer type");
	protected:
		TreeNode* lchild_;
		TreeNode* rchild_;
		T val_;

	public:
		TreeNode (T);
		virtual ~TreeNode ();
		T val ();
		void lchild (TreeNode<T>*);
		void rchild (TreeNode<T>*);
};

template <class T>
TreeNode<T>::TreeNode (T v) : lchild_(nullptr), rchild_(nullptr), val_(v) {}

template <typename T>
TreeNode<T>::~TreeNode () {
	if (lchild_) delete lchild_;
	if (rchild_) delete rchild_;
	if (val_) delete val_;
}

template <typename T>
T TreeNode<T>::val () { return val_; }

#endif
