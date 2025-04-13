#ifndef LIST_HPP
#define LIST_HPP

#include <vector>
#include "BraidedNode.hpp"

template <class T>
class List;

template <class T>
class ListNode : public Node {
	protected:
		T val_;
		friend class List<T>;
	public:
		ListNode (T);
		~ListNode ();
};

template <class T>
ListNode<T>::ListNode (T val) : Node(), val_(val) {}

template <class T>
ListNode<T>::~ListNode () { if (val_) delete val_; }

template <class T>
class List {
	private:
		ListNode<T>* header_;
		ListNode<T>* window_;
		int length_;

	public:
		List ();
		~List ();
		void val (T);
		void insert (T);
		void append (T);
		void append (List*);
		void prepend (T);
		void remove ();
		T val ();
		T next ();
		T prev ();
		T first ();
		T last ();
		int length ();
		bool isFirst ();
		bool isLast ();
		bool isHead ();
		void print (const std::string& filename);
		template <class U>
			void save_vector(std::vector<U>& data) {
				first();

				for (int i = 0; i < length(); i++, next()) {
					data.push_back(window_->val_->org_x());
					data.push_back(window_->val_->org_y());
					data.push_back(window_->val_->dest_x());
					data.push_back(window_->val_->dest_y());
				}
			}
};	

template <class T>
List<T>::List () : length_(0) {
	header_ = new ListNode<T> (nullptr);
	window_ = header_;
}

template <class T>
List<T>::~List () {
	first();
	while (length() > 0) {
		first ();
		remove ();
	}
	delete header_;
}

template <class T>
void List<T>::print (const std::string& filename) {
	first();
	std::string folder = "input";

#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif

	std::string filepath = folder + "/" + filename;
	std::ofstream out (filepath, std::ios::app);
	for (int i = 0; i < length(); i++, next())
		out << *window_->val_;
	out.close();
}

template <class T>
void List<T>::insert (T val) {
	window_ = static_cast<ListNode<T>*>(window_->insert(new ListNode<T>(val)));
	++length_;
}

template <class T>
void List<T>::prepend (T val) {
	window_ = static_cast<ListNode<T>*>(header_->insert(new ListNode<T>(val)));
	++length_;
}

template <class T>
void List<T>::append (T val) {
	window_ = static_cast<ListNode<T>*>(header_->prev()->insert(new ListNode<T>(val)));
	++length_;
}

template <class T>
void List<T>::append (List<T>* l) {
	ListNode<T>* a = static_cast<ListNode<T>*>(header_->prev());
	a->splice (l->header_);
	length_ += l->length_;
	l->header_->remove();
	l->length_ = 0;
	l->window_ = header_;
}

template <class T>
void List<T>::remove () {
	if (window_ == header_)
		return ;
	window_ = static_cast<ListNode<T>*>(window_->prev());
	delete static_cast<ListNode<T>*>(window_->next()->remove());	
	--length_;
}

template <class T>
void List<T>::val (T val) {
	if (window_ != header_)
		window_->val_ = val;
}

template <class T>
T List<T>::val () {
	return window_->val_;
}

template <class T>
T List<T>::next () {
	if (!window_) return nullptr;
	window_ = static_cast<ListNode<T>*>(window_->next());
	return window_->val_;
}

template <class T>
T List<T>::prev () {
	window_ = static_cast<ListNode<T>*>(window_->prev());
	return window_->val_;
}

template <class T>
T List<T>::first () {
	window_ = static_cast<ListNode<T>*>(header_->next());
	return window_->val_;
}

template <class T>
T List<T>::last () {
	window_ = static_cast<ListNode<T>*>(header_->prev());
	return window_->val_;
}

template <class T>
int List<T>::length () {
	return length_;
}

template <class T>
bool List<T>::isFirst () {
	return (window_ == header_->next()) && (length_ > 0);
}

template <class T>
bool List<T>::isLast () {
	return (window_ == header_->prev()) && (length_ > 0);
}

template <class T>
bool List<T>::isHead () {
	return window_ == header_;
}

#endif
