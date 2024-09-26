#include <iostream>
#include <ostream>
#include <string>

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

class Exception {
	private:
		int error_;
		std::string Message_;
		Exception () {}

	public:
		Exception (int error, std::string message) :  error_(error), Message_(message) {}
		~Exception () {}
		void print_message () { std::cout <<  "Ошибка " << error_ << ". " << Message_ << std::endl; }
};

#endif
