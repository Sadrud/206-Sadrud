#ifndef TREENODE_HPP
#define TREENODE_HPP

template <class T>
class TreeNode {
	public:
		TreeNode* lchild_;
		TreeNode* rchild_;
		T val_;

	public:
		TreeNode (T*);
		bool isEmpty ();
		virtual ~TreeNode ();
		T val ();
		void lchild (TreeNode<T>*);
		void rchild (TreeNode<T>*);
};

template <class T>
TreeNode<T>::TreeNode (T v) : lchild_(nullptr), rchild_(nullptr), val_(v) {}

template <class T>
bool TreeNode<T>::isEmpty () { return isEmpty_; }

template <typename T>
TreeNode<T>::~TreeNode () {
	if (lchild_) delete lchild_;
	if (rchild_) delete rchild_;
}

template <typename T>
T TreeNode<T>::val () { return val_; }

template <typename T>
void TreeNode<T>::lchild (TreeNode<T>* p) { lchild_ = p; }

template <typename T>
void TreeNode<T>::rchild (TreeNode<T>* p) { rchild_ = p; }

#endif
