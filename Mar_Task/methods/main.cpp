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
