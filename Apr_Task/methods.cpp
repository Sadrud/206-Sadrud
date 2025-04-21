#include <iostream>
#include <fstream>
#include <stack>
#include <random>
#include <ctime>
#include <sys/stat.h>


std::vector<std::vector<int>> generateAdjacencyMatrix(int vertices, float maxDensity, int maxEdges) {
	if (vertices <= 0 || maxDensity < 0 || maxDensity > 1)
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

	return matrix;
}


void printMatrix (std::string& folder, std::string& file, const std::vector<std::vector<int>>& g) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + '/' + file + ".txt";
	std::ofstream out(filename);

	for (const auto& row : g) {
		for (int val : row) {
			out << val << " ";
		}
		out << std::endl;
	}
	out.close();
}


void printVector (std::string& folder, std::string& file, const std::vector<int>& g) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + '/' + file + ".txt";
	std::ofstream out(filename);

	for (const auto& val : g)
		out << val << " ";
	out << std::endl;

	out.close();
}


std::vector<int> FindEulerPath(int n, std::vector<std::vector<int>>& g) {
	std::vector<int> deg (n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			deg[i] += g[i][j];

	int first = 0;
	while (!deg[first]) ++first;

	int v1 = -1,  v2 = -1;
	bool bad = false;
	for (int i = 0; i < n; ++i)
		if (deg[i] & 1)
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;

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
			if (res[i] == v1 && res[i+1] == v2 || res[i] == v2 && res[i+1] == v1)
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

	if (bad) throw std::runtime_error("Нет эйлерового пути."); //puts ("-1");
	/*else
	  for (size_t i = 0; i < res.size(); ++i) 
	  printf ("%d ", res[i]+1);
	  */
	return res;
}
