#ifndef LIST_HPP
#define LIST_HPP

template <class T>
class List {
	private:
		ListNode<T>* header_;
		ListNode<T>* window_;
		int length_;

	public:
		List ();
		~List ();
		T insert (T);
		T append (T);
		List* append (List*);
		T prepend (T);
		T remove ();
		void val ();
		T next ();
		T prev ();
		T first ();
		T last ();
		int length ();
		bool isFirst ();
		bool isLast ();
		bool isHead ();
};	

template <class T>
List<T>::List () : length_(0) {
	header_ = new ListNode<T> (nullptr);
	window
}

#endif
