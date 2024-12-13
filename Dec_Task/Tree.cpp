#include "Tree.hpp"
#include <iostream>

int Process (TreeNode* node) { return calculatePaths (node, 0); }

int calculatePaths (TreeNode* node, int currentNumber) {
	if (!node) return 0;

	currentNumber = currentNumber * 10 + node->value;

	if (!node->left && !node->right) return currentNumber;

	return calculatePaths (node->left, currentNumber) + calculatePaths(node->right, currentNumber);
}

//для создания списка, из которого будем конструировать дерево
TreeNode* addNode (int value, TreeNode* prev) {
	TreeNode* p = new TreeNode (value);
	if (!prev) {  prev = p; }
	else { prev->right = p;	}
	return p;
}

//создание "списка-уровня"
TreeNode* TListFill (int lenLevel) {
	TreeNode* first = nullptr;
	int value = 0;
	std::cin >> value;
	if (std::cin.fail() || value > 9 || value < 0) return nullptr;
	first = new TreeNode (value);
	TreeNode* copyFirst = first;

	for (int j = 1; j < lenLevel; j++) {
		int num = 0;
		std::cin >> num;
		if (std::cin.fail() || num > 9 || num < 0) return nullptr;
		copyFirst = addNode (num, copyFirst);
	}
	return first;
}

//воссоединение детей и родителей
TreeNode* connect (int lenLevel, TreeNode* parentList, TreeNode* childList) {
	//следующие два указателя образуют пару детей одного родителя
	TreeNode* lag = childList;
	TreeNode* ahead = nullptr;
	if (childList) ahead  = childList->right;

	//следующие два указателя два соседних родителя
	TreeNode* parent = parentList;
	TreeNode* parentNext = nullptr;
	if (parentList) parentNext = parentList->right;

	for (int k = 0; k < lenLevel/2; k++) {
		parent->left = lag;
		parent->right = ahead;
		if (lag && lag->right) lag = lag->right->right;
		if (ahead && ahead->right) ahead = ahead->right->right;
		parent = parentNext;
		if (parentNext) parentNext = parentNext->right;
	}
	return childList;
}

void add (TreeNode* node, int quantity) {
	int lenLevel = 2;//длина уровня

	TreeNode* above = node;//уровень, который мы хотим связать с нижним
	TreeNode* below = nullptr;//нижний уровень

	for (int i = 1; i < quantity; i++) {
		std::cout << "Уровень " << i+1 << std::endl;

		//создание уровня списком
		below = TListFill (lenLevel);
		if (below == nullptr) throw std::invalid_argument ("Введено некорректное значение.");

		//связывание двух листов в дерево
		above = connect(lenLevel, above, below);
		lenLevel *= 2;
	}
	above = connect(lenLevel, above, nullptr);

}

void del (TreeNode* node) {
	if (!node) return;
	del (node->left);
	del (node->right);
	delete (node);
	node = nullptr;
}

void printTree(TreeNode* root, int depth) {
	if (!root) return;
	for (int i = 0; i < depth; ++i) {
		std::cout << "  ";
	}
	std::cout << root->value << std::endl;

	printTree(root->left, depth + 1);
	printTree(root->right, depth + 1);
}

