#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../Exception.hpp"
#include "Point.hpp"
#include <sys/stat.h>

class Rectangle {
	public:
		Point sw; 	// bottom left corner
		Point ne;	// upper right corner
		int id;		// identifier
		
		Rectangle () {}
		Rectangle (Point sw_, Point ne_, int id_ = -1) : sw(sw_), ne(ne_), id(id_) {
			if (sw_ == ne_) { std::cout << sw_.x << ' ' << sw_.y << ' ' << ne_.x << ' ' << ne_.y << std::endl; throw Exception(3, "Прямоугольник не создается."); }
			if (!(sw < ne)) { std::cout << sw_.x << ' ' << sw_.y << ' ' << ne_.x << ' ' << ne_.y << std::endl;  throw Exception(3, "Прямоугольник задан неправильно."); }
		}
		~Rectangle () {}
		friend std::ostream& operator<< (std::ostream& os, Rectangle& rect) {
			os << rect.sw.x << " " << rect.sw.y << " " << rect.sw.x << " " << rect.ne.y << " " << rect.ne.x << " " << rect.ne.y << " " << rect.ne.x << " " << rect.sw.y << std::endl;
			return os;
		}
		void print (const std::string& filename, int len) {
			std::string folder = "input";

			#ifdef _WIN32
				mkdir(folder.c_str());
			#else
				mkdir(folder.c_str(), 0777);
			#endif

			std::string filepath = folder + "/" + filename;
			std::ofstream out(filepath);
			for (int i = 0; i < len; i++)
				out << *(this+i);
			out.close();
		}
};

#endif
