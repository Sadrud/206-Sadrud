/*!
	\file tests.cpp
	\brief Создание тестов.
	\author Sadrud
	\date 2025
*/


#include "../methods/methods.cpp"

/*!
	\brief Пространство имен для тестов
	\details В тесте создается матрица смежности. Также создается название файла, в котором будет хранится матрица и эйлеров путь.
	\param [in] folder, vertices, maxEdges, density Название папки, в которой будут хранится матрицы смежности, количесвто вершин, максимальное количество ребер, выходящих из одной вершины, и плотность распределения ребер по вершинам
*/

namespace GraphTests {
	std::vector<std::vector<int>> randomTest (std::string folder, int vertices, bool hasPath) {
		std::vector<std::vector<int>> g = generateAdjacencyMatrix(vertices, hasPath);

		std::string filename = 
			"The adjacency matrix of the graph: vertices - " + std::to_string(vertices) 
			+ ", path or cycle - " + (hasPath ? "Cycle" : "Path");

		printMatrix (folder, filename, g);
		return g;
	}
}
