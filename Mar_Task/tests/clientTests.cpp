#include "testsCreate.cpp"

namespace ClientTests {
	void randomTest1 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}

	void randomTest2 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}

	void randomTest3 (const std::string& folder, int q, int s, int p) {
		std::string ran("Рандомные прямоугольники. Количество: ");
		std::string raz(". Разброс: ");
		std::string a(ran + std::to_string(q) + raz + std::to_string(s));
		randomTests(folder, a, q, s, p);
	}
};
