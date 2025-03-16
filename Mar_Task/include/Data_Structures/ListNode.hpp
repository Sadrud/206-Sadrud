#ifndef LISTNODE_HPP
#define LISTNODE_HPP

template <class T>
class ListNode : public Node {
	protected:
		T* val_;
	public:
		ListNode (T);
};

template <class T>
ListNode<T>::ListNode (T val) : Node(), val_(val) {}

#endif
