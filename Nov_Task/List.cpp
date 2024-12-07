#ifndef LIST_CPP
#define LIST_CPP

#include "List.hpp"

List::~List () {
	ListNode* currentNode = first;
	while (currentNode) {
		ListNode* nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}

void List::operator() (int value) {
	ListNode* p = new ListNode (value);
	if (!first) { first = p; }
	else {
		ListNode* last = first;
		while (last->next != nullptr) {	last = last->next; }
		last->next = p;
	}
}

bool List::Process () {
	//если список пуст или содержит один элемент, то он по определению считается палиндромным
	if (!first || !first->next) return true;

	//переход к середине списка
	ListNode* slow = first;
	ListNode* fast = first;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	//переворачивание второй половины списка
	ListNode* prev = nullptr;
	ListNode* curr = slow;
	while (curr) {
		ListNode* nextNode = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nextNode;
	}

	//сравнение первой и второй половин
	ListNode* firstHalf = first;
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

	//восстановление списка
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

//печать
std::ostream& operator<< (std::ostream& os, List& list) {
	if (list.first == nullptr) { os << "Список пустой." << std::endl; return os; }

	for (ListNode* ptr = list.first; ptr != nullptr; ptr = ptr->next) { os << ptr->value << " "; }
	os << std::endl;
	return os;
}

#endif
