/*!
  \file clientTests.cpp
  \brief Создание тестов.
  \author Sadrud
  \date 2025
  */

#include "testsCreate.cpp"
/*!
 \brief Пространство имен для тестов.
 3 функции, которые создают тесты для клиента. Все однотипные: создают папку, затем в ней файл с числами. 
 В качестве аргументов принимают название создаваемой папки, и 3 числа, характеризующие распределение прямоугольников по плоскости 
 (количество, разброс по плоскости и максимальная длина стороны прямоугольника)
 */
namespace ClientTests {
	/*
	 /btief Первый тест
	 */
	void randomTest1 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}

	/*
	 /brief Второй тест
	 */
	void randomTest2 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}

	/*
	 /brief Третий тест
	 */
	void randomTest3 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}
};
