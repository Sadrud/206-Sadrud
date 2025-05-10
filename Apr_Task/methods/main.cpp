#include "../tests/tests.cpp"

int main () {
	try {
		GraphTests::randomTest (100, 0.2, 5);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
