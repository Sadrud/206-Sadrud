#ifndef LIST_HPP
#define LIST_HPP

#include <ostream>

struct ListNode {
	int value;
	ListNode* next;

	ListNode (): next(nullptr) {}
	ListNode (int k): value(k), next(nullptr) {}
	bool operator== (ListNode* node) { return (value == node->value); }

	ListNode add (int new_val);

};

class List {
	ListNode* first;

	public:
	List () : first(nullptr) {}
	~List ();

	void opearator() (int value);
	friend std::ostream& operator<< (std::ostream& os, ListNode* node)

	int len (ListNode* head);
	bool Process_N (ListNode* head);
	void Center (ListNode* node, ListNode* next, bool* eq, int* num);

	bool Process (ListNode* head);

}

#endif
