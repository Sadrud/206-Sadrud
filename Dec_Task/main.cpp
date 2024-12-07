#include <iostream>
#include "Tree.hpp"

int main () {
	TreeNode* node = new TreeNode ();
	std::cout << "Введите значения:" << std::endl;
	int k = 0;
	std::cin >> k;
	if (std::cin.fail()) std::cout << "Не число" << std::endl;
	add (k, node);
	del (node);
	return 0;
}
