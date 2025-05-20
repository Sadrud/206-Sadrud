/*!
  \file methods.cpp
  \brief Основные методы для вычислений..
  \author Sadrud
  \date 2025
  */


#include <iostream>
#include <fstream>
#include <stack>
#include <random>
#include <ctime>
#include <sys/stat.h>
#include <cstdlib>
#include <algorithm>
#include <omp.h>
#include <chrono>

/*!
  \brief Создание рандомной матрицы смежности (по сути создание рандомного графа)
  \param[in] vertices, maxDensity, maxEdges Количество вершин в графе, плотность распределения ребер, максимальное количество ребер, выходящее из вершины
  \return Возвращает сгенерированную матрицу
  */
std::vector<std::vector<int>> generateAdjacencyMatrix(int n, bool hasPath) {

	std::srand(std::time(0));
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
	std::vector<int> degree(n, 0);

	for (int i = 1; i < n; ++i) {
		int j = std::rand() % i;
		matrix[i][j]++;
		matrix[j][i]++;
		degree[i]++;
		degree[j]++;
	}

	int extraEdges = std::rand() % (n * 2);
	for (int k = 0; k < extraEdges; ++k) {
		int i = rand() % n;
		int j = rand() % n;
		if (i == j) continue;
		matrix[i][j]++;
		matrix[j][i]++;
		degree[i]++;
		degree[j]++;
	}

	std::vector<int> oddVertices;
	for (int i = 0; i < n; ++i) {
		if (degree[i] % 2 != 0) {
			oddVertices.push_back(i);
		}
	}

	if (hasPath) {
		while (oddVertices.size() > 2) {
			int u = oddVertices.back(); oddVertices.pop_back();
			int v = oddVertices.back(); oddVertices.pop_back();
			matrix[u][v]++;
			matrix[v][u]++;
			degree[u]++;
			degree[v]++;
		}
		while (oddVertices.size() < 2) {
			int u = rand() % n;
			int v = rand() % n;
			if (u == v) continue;
			matrix[u][v]++;
			matrix[v][u]++;
			degree[u]++;
			degree[v]++;
			if (degree[u] % 2 != 0) oddVertices.push_back(u);
			if (degree[v] % 2 != 0) oddVertices.push_back(v);
		}
	} else {
		while (oddVertices.size() >= 2) {
			int u = oddVertices.back(); oddVertices.pop_back();
			int v = oddVertices.back(); oddVertices.pop_back();
			matrix[u][v]++;
			matrix[v][u]++;
			degree[u]++;
			degree[v]++;
		}
	}

	return matrix;

	/*if (vertices <= 0 || maxDensity < 0 || maxDensity > 1)
	  throw std::invalid_argument("Invalid arguments");

	  std::mt19937 gen(time(0));
	  std::uniform_real_distribution<float> probDist(0.0, 1.0);
	  std::uniform_int_distribution<int> edgeCountDist(0, maxEdges);

	  std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices));

	  for (int i = 0; i < vertices; ++i) {
	  for (int j = i; j < vertices; ++j) {
	  if (i == j) {
	  matrix[i][j] = 0;
	  continue;
	  }

	  if (probDist(gen) <= maxDensity) {
	  matrix[i][j] += edgeCountDist(gen);
	  matrix[j][i] = matrix[i][j];
	  }
	  }
	  }

	  return matrix;*/
}


/*!
  \brief Печать матрицы
  \param[in] folder, file, g Название папки, в которой хранятся файлы, название файла для хранения матрицы смежности, сама матрица смежности 
  */
void printMatrix (std::string& folder, std::string& file, const std::vector<std::vector<int>>& g) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + "/" + file + ".txt";
	std::ofstream out(filename, std::ios::app);

	for (const auto& row : g) {
		for (int val : row) {
			out << val << " ";
		}
		out << std::endl;
	}
	out.close();
}


/*!
  \brief Печать вектора (эйлерового пути)
  \param[in] folder, file, g Название папки, в которой хранятся файлы, название файла для хранения эйлерового пути, сам эйлеров путь
  */
void printVector (std::string& folder, std::string& file, const std::vector<int>& g) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + "/" + file + ".txt";
	std::ofstream out(filename, std::ios::app);

	for (const auto& val : g)
		out << val << " ";
	out << std::endl;

	out.close();
}


/*!
  \brief Основной метод - нахождение эйлерового пути в графе
  \Функция работает с матрицей смежности графа.
  \Сначала она проверяет, существует ли вообще эйлеров путь (также и эйлеров цикл).
  \Далее она выбирает произвольную вершину, и начиная с нее уже начинает бегать по графу. Обязательно она найдет какой-либо путь (необязательно эйлеров).
  \И, в итоге, имея путь, функция опять проходит по всем вершинам этого пути, и вычитает ребро из матрицы смежности, и проделывает так, пока не пройдет путь.
  \Если получилась нулевая матрица, по найденный путь эйлеров, иначе нет.
  \param[in] n, g Количесвто вершин и матрица смежности
  \return Возвращает вектор, содержащий эйлеров путь
  */
std::vector<int> FindEulerPath(int n, std::vector<std::vector<int>> g) {

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<int> deg (n, 0);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			deg[i] += g[i][j];

	int first = 0;
	while (!deg[first]) ++first;

	int v1 = -1,  v2 = -1;
	bool bad = false;
	for (int i = 0; i < n; ++i)
		if (deg[i] & 1) {
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;
		}

	if (v1 != -1)
		++g[v1][v2],  ++g[v2][v1];

	std::stack<int> st;
	st.push (first);
	std::vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < n; ++i)
			if (g[v][i])
				break;
		if (i == n)
		{
			res.push_back (v);
			st.pop();
		}
		else
		{
			--g[v][i];
			--g[i][v];
			st.push (i);
		}
	}

	if (v1 != -1)
		for (size_t i = 0; i+1 < res.size(); ++i)
			if (((res[i] == v1) && (res[i+1] == v2)) || ((res[i] == v2) && (res[i+1] == v1)))
			{
				std::vector<int> res2;
				for (size_t j = i+1; j < res.size(); ++j)
					res2.push_back (res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back (res[j]);
				res = res2;
				break;
			}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (g[i][j])
				bad = true;

	if (bad) throw std::runtime_error("Нет эйлерового пути.");

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Время выполнения обычного алгоритма: " << elapsed.count() << " секунд\n";

	return res;
}

std::vector<int> FindEulerPath_parallel(int n, std::vector<std::vector<int>> g) {

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<int> deg(n, 0);

#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
#pragma omp atomic
			deg[i] += g[i][j];

	int first = 0;
	while (first < n && !deg[first]) ++first;

	int v1 = -1, v2 = -1;
	bool bad = false;

#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		if (deg[i] & 1) {
#pragma omp critical
			{
				if (v1 == -1)
					v1 = i;
				else if (v2 == -1)
					v2 = i;
				else
					bad = true;
			}
		}
	}

	if (v1 != -1) {
		++g[v1][v2];
		++g[v2][v1];
	}

	std::stack<int> st;
	st.push(first);
	std::vector<int> res;

	while (!st.empty()) {
		int v = st.top();
		int i = 0;
		for (; i < n; ++i)
			if (g[v][i])
				break;
		if (i == n) {
			res.push_back(v);
			st.pop();
		} else {
			--g[v][i];
			--g[i][v];
			st.push(i);
		}
	}

	if (v1 != -1) {
		for (size_t i = 0; i + 1 < res.size(); ++i) {
			if ((res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1)) {
				std::vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);
				res = res2;
				break;
			}
		}
	}

#pragma omp parallel for collapse(2) reduction(|:bad)
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (g[i][j])
				bad = true;

	if (bad)
		throw std::runtime_error("Нет эйлерового пути.");

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Время выполнения распаралелленного алгоритма: " << elapsed.count() << " секунд\n";

	return res;
}
