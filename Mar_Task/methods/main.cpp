/*!
  \file main.cpp
  \brief Проверка работы алгоритма. Никак не относится к клиент-серверному приложению. Можно проигнорировать.
  \author Sadrud
  \date 2025
  */

#include "Methods.hpp"
#include "../tests/mainTest.cpp"

int main () {
	try {
		randomTest();
	} catch (Exception& ex) { ex.print_message(); }
	try {
		randomTest2 ();
	} catch (Exception& ex) { ex.print_message(); }
	try {
		randomTest3 ();
	} catch (Exception& ex) { ex.print_message(); }
	diagonalTest ();
	shrinkTest ();
	latticeTest();
	ladderTest ();

	return 0;
}
