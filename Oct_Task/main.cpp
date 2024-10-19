#include <iostream>
#include "GCD_LCM.hpp"

int main() {
	try {
		Int a(15), b(20), gcdResult, lcmResult;

		try {
			GCD(a, b, gcdResult);
			//std::cout << "GCD (Int): " << dynamic_cast<Int&>(gcdResult).getValue() << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Ошибка в GCD (Int): " << e.what() << std::endl;
		}


		try {
			LCM(a, b, lcmResult);
			std::cout << "LCM (Int): " << dynamic_cast<Int&>(lcmResult).getValue() << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Ошибка в LCM (Int): " << e.what() << std::endl;
		}

		Long c(15), d(20), gcdLongResult, lcmLongResult;

		try {
			GCD(c, d, gcdLongResult);
			std::cout << "GCD (Long): " << dynamic_cast<Long&>(gcdLongResult).getValue() << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Ошибка в GCD (Long): " << e.what() << std::endl;
		}

		try {
			LCM(c, d, lcmLongResult);
			std::cout << "LCM (Long): " << dynamic_cast<Long&>(lcmLongResult).getValue() << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Ошибка в LCM (Long): " << e.what() << std::endl;
		}


		Int n(15), m(0), result;
		try {
			n /= m;
			std::cerr << "Тест деления на ноль провален: исключение не выброшено" << std::endl;
		} catch (const std::invalid_argument& e) {
			std::cout << "Тест деления на ноль пройден: " << e.what() << std::endl;
		}
	}

	catch (const std::bad_cast& e) { std::cerr << "Ошибка приведения типов: " << e.what() << std::endl; } 
	catch (...) { std::cerr << "Неизвестная ошибка" << std::endl; }

	try {
		Int x(15), y(20), gcdResult_xy, lcmResult_xy;

		GCD(x, y, gcdResult_xy);
		int gcd_value = dynamic_cast<Int&>(gcdResult_xy).getValue();
		std::cout << "GCD (Int): " << gcd_value << std::endl;

		LCM(x, y, lcmResult_xy);
		int lcm_value = dynamic_cast<Int&>(lcmResult_xy).getValue();
		std::cout << "LCM (Int): " << lcm_value << std::endl;

		Long p(15), q(20), gcdLongResult_pq, lcmLongResult_pq;

		GCD(p, q, gcdLongResult_pq);
		long gcdLong_value = dynamic_cast<Long&>(gcdLongResult_pq).getValue();
		std::cout << "GCD (Long): " << gcdLong_value << std::endl;

		LCM(p, q, lcmLongResult_pq);
		long lcmLong_value = dynamic_cast<Long&>(lcmLongResult_pq).getValue();
		std::cout << "LCM (Long): " << lcmLong_value << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
}
