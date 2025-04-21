#include "methods.cpp"

namespace GraphTests {
	void randomTest (int vertices, float density, int maxEdges) {
		std::vector<std::vector<int>> g = generateAdjacencyMatrix(vertices, density, maxEdges);
		
		std::string folder = "input";
		std::string filename = 
			"Матрица смежности графа: вершин - " + std::to_string(vertices) 
			+ ", плотность ребер - " + std::to_string(density) 
			+ ", максимум ребер - " + std::to_string(maxEdges);

		printMatrix (folder, filename, g);

		std::vector<int> path = FindEulerPath(vertices, g);

		folder = "output";
		filename = "Путь по вершинам: вершин - " + std::to_string(vertices)
			+ ", плотность ребер - " + std::to_string(density)
			+ ", максимум ребер - " + std::to_string(maxEdges);
		printVector (folder, filename, path);
	}
}
