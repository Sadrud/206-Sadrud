#include "tests.cpp"

int main () {
	try {
		GraphTests::randomTest (10, 0.2, 3);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
