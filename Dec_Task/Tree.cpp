#include "Tree.hpp"

int Tree::calculatePaths (TreeNode* node, int currentSum) {
	if (!node) return 0;
	
	currentSum = currentSum*10 + node->value;
	
	if (!node->left && !node->right) return currentSum;

	return calculatePaths(node->lest, currentSum) + calculatePaths(node->right, currentSum);
}

void Tree::operator() (int val) {
	if (root) return new Node(val);

	
}
