#include <iostream>
#include "Tree.hpp"

int main () {
	try {
		int quantity = 0;
		std::cout << "Введите количество цифр самого большого вашего числа (учтите, что -1 вводится, чтобы в дереве больше не было узлов):" << std::endl;
		std::cin >> quantity;
		if (std::cin.fail() || quantity == 0) { throw std::invalid_argument ("Зачем вам программа, которая не считает ничего?"); }

		std::cout << "Вводите числа по уровням дерева: " << std::endl;
		std::cout << "Уровень " << 1 << std::endl;
		int num = 0;
		std::cin >> num;
		if (std::cin.fail() || num > 9 || num < 1) throw std::invalid_argument ("Введено некорректное значение.");
		TreeNode* node = new TreeNode (num);

		add (node, quantity);
		/*	std::cout << node->value << std::endl;
			std::cout << std::endl;
			std::cout << node->left->value << std::endl;
			std::cout << node->right->value << std::endl;
			std::cout << std::endl;
			std::cout << node->left->left->value << std::endl;
			std::cout << node->left->right->value << std::endl;
			std::cout << node->right->left->value << std::endl;
			std::cout << node->right->right->value << std::endl;
			*/
		int sum = Process (node);
		std::cout << "Сумма чисел в ветках дерева равна: " << sum << std::endl;

		printTree (node, 0);

		del (node);

		/*TreeNode* root = new TreeNode(1);
		  root->left = new TreeNode(2);
		  root->right = new TreeNode(5);
		  root->left->left = new TreeNode(3);
		  root->left->right = new TreeNode(4);
		  root->right->left = new TreeNode(6);
		  root->right->right = new TreeNode(7);

		// Проверяем функцию
		std::cout << "Сумма всех чисел: " << Process(root) << std::endl; // Ожидаем: 124 + 125 + 13 = 262

		// Освобождаем память
		delete root->right->right;
		delete root->right->left;
		delete root->left->left;
		delete root->left->right;
		delete root->left;
		delete root->right;
		delete root;
		*/
	} catch (const std::exception& e) { std::cerr << e.what() << std::endl;	}
	return 0;
}
