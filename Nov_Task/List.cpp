#ifndef LIST_CPP
#define LIST_CPP

#include "List.hpp"

List::~List () {
	Node* currentNode = first;
	while (currentNode) {
		Node* nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}

int List::len (ListNode* head) {
	int n = 0;
	for (ListNode* node = head; node != nullptr; node = node->next) n++;
	return n;
}

void List::Center (ListNode* node, ListNode* next, bool* eq, int* index, int* num) {
	if (*index != *num/2) {
		(*index)++;
		node = next;
		next = next->next;
		Center(node, next, eq, index, num);
	}

	if (*eq == false) return;

	if (node == next) { *eq = true; next = next->next; }
}

bool List::Process_N (ListNode* head) {
	ListNode* node = head;
	int n = len(node);

	int zero = 0;
	int* index = &zero;
	bool qu = true;
	bool* eq = &qu;
	ListNode* next = node->next;

	stCenter (node, next, eq, index, &n);
	return *eq;
}

bool List::Process (ListNode* head) {
	if (!head || !head->next) return true;

	ListNode* slow = head;
	ListNode* fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	ListNode* prev = nullptr;
	ListNode* curr = slow;
	while (curr) {
		ListNode* nextNode = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nextNode;
	}

	ListNode* firstHalf = head;
	ListNode* secondHalf = prev;
	bool isPalindrome = true;

	while (secondHalf) {
		if (firstHalf->value != secondHalf->value) {
			isPalindrome = false;
			break;
		}
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	curr = prev;
	prev = nullptr;
	while (curr) {
		ListNode* nextNode = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nextNode;
	}

	return isPalindrome;
}

std::ostream& operator<< (std::ostream& os, ListNode* node) {
	if (node == nullptr) { os << "Список пустой." << std::endl; return os; }

	for (ListNode* ptr = node; ptr != nullptr; ptr = ptr->next) { os << ptr->value; }
	os << std::endl;
	return os;
}

#endif
