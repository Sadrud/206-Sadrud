#include "Tree.hpp"
#include <iostream>

int Tree::calculatePaths (TreeNode* node, int currentSum) {
	if (!node) return 0;
	
	currentSum = currentSum*10 + node->value;
	
	if (!node->left && !node->right) return currentSum;

	return calculatePaths(node->left, currentSum) + calculatePaths(node->right, currentSum);
}

void add (int val, TreeNode* node) {
	if (val == -1) { delete node; return; }
	node->value = val;

	TreeNode* n1 = new TreeNode();
	TreeNode* n2 = new TreeNode();
	node->left = n1;
	node->right = n2;
	int m1 = 0, m2 = 0;
	std::cin >> m1;
	if (std::cin.fail()) { std::cout << "Не число" << std::endl; return; }
	std::cin >> m2;
	if (std::cin.fail()) { std::cout << "Не число" << std::endl; return; }

	add (m1, n1);
	add (m2, n2);
}

void del (TreeNode* node) {
	std::cout << "Итерация" << std::endl;
	if (node->left == nullptr && node->right == nullptr) { delete node; return ; }
	TreeNode* n1 = node->left;
	TreeNode* n2 = node->right;
	delete node;
	del (n1);
	del (n2);
}
