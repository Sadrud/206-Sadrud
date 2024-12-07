#include <iostream>
#include "List.hpp"

int main () {
	List a;
	for (int i = 0; i < 50; ++i) { a(i); }
	for (int i = 49; i >= 0; --i) { a(i); }
	std::cout << a << std::endl;

	if (a.Process() == true) { std::cout << "True" << std::endl; }
	else { std::cout << "False" << std::endl; }

	List b;
	for (int i = 0; i < 100; i++) { if (20 - i < 0) { b(i - 20); } else { b(20 - i); } }
	std::cout << b << std::endl;
	
	if (b.Process() == true) { std::cout << "True" << std::endl; }
        else { std::cout << "False" << std::endl; }

	List c;
	int count = 0;
	std::cout << "Введите количество элементво в списке:" << std::endl;
	std::cin >> count;

	std::cout << "Введите числа по порядку:" << std::endl;

	for (int i = 0; i < count; ++i) {
		int num = 0;
		std::cin >> num;
		c(num);
	}

	if (c.Process() == true) { std::cout << "True" << std::endl; }
        else { std::cout << "False" << std::endl; }

	return 0;
}
