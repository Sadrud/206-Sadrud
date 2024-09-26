#include <iostream>
#include <ostream>
#include <string>
#include "Exception.hpp"
#include "Plane.cpp"
#include "Plane.hpp"

int main () {
	Set_points a;
	a.p_add(0, 0);
	a.p_add(12, 124);
	a.p_add(34, 32);
	a.p_add(154, 65);
	
	try { a.p_add(0,0); }
	catch (Exception ex){ ex.print_message(); }

	Set_points b = a;
	
	try { b.p_add(154, 65); }
	catch (Exception ex){ ex.print_message(); }
	
	return 0;
}
