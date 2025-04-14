/*!
  \brief Создание тестов.
  \author Sadrud
  \date 2025
  */

#include <fstream>
#include <random>
#include <sys/stat.h>

//! Малое число, чтобы при генерации пары точек, они не находились на одной прямой, параллельной осям координат. 
double eps = 1e-1;

/*
 * @brief Функция для создания рандомных прямоугольников
 * @param[in] folder, file, quantity, spread, area Название папки, в которой хранится файл, количество прямоугольников, разброс по оси координат и максимальное растояние между двумя точками..
 * @details Функция создает папку, в которой будут хранится файлы со значениями вершин прямоугольков.
 * Вершины прямоугольков расставлены по часовой стрелке, начиная с левого нижнего угла. В строке расположены 8 чисел, которые образуют 4 точки. Происходит запись чисел построчно.
 */
void randomTests (const std::string& folder, const std::string& file, int quantity, int spread, int area) {

#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + '/' + file + ".txt";
	std::ofstream out(filename);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, spread);
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<> dist2(0, area);

	for (int i = 0; i < quantity; i++) {
		double x1 = dist(gen);
		double y1 = dist(gen);
		double x2 = x1 + dist2(gen2) + eps;
		double y2 = y1 + dist2(gen2) + eps;
		out << x1 << " " << y1 << " " << x1 << " " << y2 << ' ' << x2 << ' ' << y2 << ' ' << x2 << ' ' << y1 << "\n";
	}
	out.close();
}
