#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;
//ex1
vector<vector<int>> convertMatrixToList(const string& filename);
//ex2
vector<vector<int>> convertListToMatrix(const string& filename);
//ex3
bool isDirected(const vector<vector<int>>& adjMatrix);
int countVertices(const vector<vector<int>>& adjMatrix);
int countEdges(const vector<vector<int>>& adjMatrix);
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix);
bool isCompleteGraph(const vector<vector<int>>& adjMatrix);
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix);
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);
//ex4
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);
//ex5
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix);
//ex6
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);
//ex7
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
//ex8
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);
//ex9
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertMatrixToList(const string& filename) {
	vector<vector<int>> List;
	string line;
	ifstream inFile(filename);
	getline(inFile, line);
	vector<int> size_matrix;
	int size = stoi(line);
	size_matrix.push_back(size);
	List.push_back(size_matrix);
	while (getline(inFile, line)) {
		vector<int> row;
		int count = 0;
		int a[100];
		int size_row = line.size();
		for (int i = 0; i < size_row; i++) {
			if (line[i] == '1') {
				a[count++] = i;
			}
		}
		row.push_back(count);
		for (int i = 0; i < count; i++) {
			row.push_back(a[i]);
		}
		List.push_back(row);
	}
	return List;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
	vector<vector<int>> Graph;
	ifstream inFile(filename);
	string line;
	getline(inFile, line);
	int size = stoi(line);
	Graph.push_back({ size });

	while (getline(inFile, line)) {
		vector<int> row(size, 0);
		stringstream ss(line);
		int count, neighbor;
		ss >> count;
		for (int i = 0; i < count; ++i) {
			ss >> neighbor;
			if (neighbor >= 0 && neighbor < size) {
				row[neighbor] = 1;
			}
		}
		Graph.push_back(row);
	}
	return Graph;
}
bool isDirected(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	for (int i = 1; i <= size; i++) {
		for (int j = 0; j < size; j++) {
			if (i - 1 != j) {
				if (adjMatrix[i][j] != adjMatrix[j + 1][i - 1]) {
					return false;
				}
			}
		}
	}
	return true;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix[0][0];
}

int countEdges(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];

	int count = 0;
	bool isDirected = false;

	for (int i = 1; i <= size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (adjMatrix[i][j] == 1) count++;
			if (!isDirected && adjMatrix[i][j] != adjMatrix[j + 1][i - 1]) isDirected = true;
		}
	}

	if (!isDirected) count /= 2;

	return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> isolatedVertices;
	int size = adjMatrix[0][0];
	for (int i = 1; i <= size; i++) {
		bool isolated = true;
		for (int j = 0; j < size; j++) {
			if (adjMatrix[i][j] == 1) {
				isolated = false;
				break;
			}
		}
		if (isolated) {
			isolatedVertices.push_back(i - 1);
		}
	}
	return isolatedVertices;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	for (int i = 1; i <= size; i++) {
		for (int j = i; j < size; j++) {
			if (i - 1 == j && adjMatrix[i][j] != 0) {
				return false;
			}
			if (i - 1 != j && adjMatrix[i][j] != 1) {
				return false;
			}
		}
	}
	return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	vector<int> color(size, -1);
	for (int i = 0; i < size; i++) {
		if (color[i] == -1) {
			queue<int> q;
			color[i] = 0;
			q.push(i);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int j = 0; j < size; j++) {
					if (adjMatrix[u + 1][j] == 1 && color[j] == -1) {
						if (color[u] == 1) color[j] = 0;
						else color[j] = 1;
						q.push(j);
					}
					if (adjMatrix[u + 1][j] && color[j] != -1) {
						if (color[u] == color[j]) return false;
						else continue;
					}
				}
			}
		}
	}
	return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	vector<int> color(size, -1);
	for (int i = 0; i < size; i++) {
		if (color[i] == -1) {
			queue<int> q;
			color[i] = 0;
			q.push(i);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int j = 0; j < size; j++) {
					if (adjMatrix[u + 1][j] == 1 && color[j] == -1) {
						if (color[u] == 1) color[j] = 0;
						else color[j] = 1;
						q.push(j);
					}
					if (adjMatrix[u + 1][j] && color[j] != -1) {
						if (color[u] == color[j]) return false;
						else continue;
					}
				}
			}
		}
	}
	for (int i = 1; i <= size; i++) {
		for (int j = 0; j < size; j++) {
			if ((i - 1) != j) {
				if (color[i - 1] == color[j] && adjMatrix[i][j] == 1) return false;
				if (color[i - 1] != color[j] && adjMatrix[i][j] == 0) return false;
			}
		}
	}
	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	vector<vector<int>> result(size, vector<int>(size, 0));
	for (int i = 1; i <= size; i++) {
		for (int j = 0; j < size; j++) {
			if (adjMatrix[i][j] == 1 || adjMatrix[j + 1][i - 1] == 1) {
				result[i - 1][j] = result[j][i - 1] = 1;
			}
		}
	}
	return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix[0][0];
	vector<vector<int>> complement(n, vector<int>(n, 0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i + 1 != j && adjMatrix[i + 1][j] == 0) {
				complement[i][j] = 1;
			}
		}
	}

	return complement;
}

void DFS(int u, vector<vector<int>>& adjMatrix, vector<int>& result) {
	int size = adjMatrix.size();
	for (int v = 0; v < size; v++) {
		while (adjMatrix[u][v] > 0) {
			adjMatrix[u][v]--;
			adjMatrix[v][u]--;
			DFS(v, adjMatrix, result);
		}
	}
	result.push_back(u);
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	vector<vector<int>> temp(size, vector<int>(size, 0));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[i][j] = adjMatrix[i + 1][j];
		}
	}
	vector<int> result;
	DFS(0, temp, result);
	reverse(result.begin(), result.end());
	return result;
}

void dfsTree(const vector<vector<int>>& graph, int u, vector<bool>& visit, vector<vector<int>>& result, int parent = -1) {
	visit[u] = true;
	if (parent != -1) {
		result.push_back({ parent, u });
	}
	for (int v = 0; v < (int)graph.size(); v++) {
		if (graph[u][v] == 1 && !visit[v]) {
			dfsTree(graph, v, visit, result, u);
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<vector<int>> result;
	int size = adjMatrix[0][0];
	vector<bool> visit(size, false);
	vector<vector<int>> temp(size, vector<int>(size));
	for (int i = 1; i <= size; i++)
		for (int j = 0; j < size; j++)
			temp[i - 1][j] = adjMatrix[i][j];
	dfsTree(temp, start, visit, result);
	return result;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<vector<int>> result;
	int size = adjMatrix[0][0];
	vector<bool> visit(size, false);
	queue<int> q;
	visit[start] = true;
	q.push(start);
	while (!q.empty()) {
		vector<int> line;
		int temp = q.front();
		q.pop();
		for (int i = 0; i < size; i++) {
			if (!visit[i] && adjMatrix[temp + 1][i] == 1) {
				visit[i] = true;
				line.push_back(temp);
				line.push_back(i);
				result.push_back(line);
				q.push(i);
			}
		}
	}
	return result;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int size = adjMatrix[0][0];
	vector<bool> visit(size, false);
	queue<int> q;
	visit[u] = true;
	q.push(u);
	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		for (int i = 1; i <= size; i++) {
			if (!visit[i] && adjMatrix[temp][i] == 1) {
				visit[i] = true;
				q.push(i);
			}
		}
	}
	if (visit[v] == true) return true;
	return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix[0][0];
	vector<int> dist(n, INT_MAX);
	vector<int> pre(n, -1);
	vector<bool> visit(n, false);

	dist[start] = 0;
	for (int i = 0; i < n; i++) {
		int u = -1;
		int minDist = INT_MAX;
		for (int j = 0; j < n; j++) {
			if (!visit[j] && dist[j] < minDist) {
				minDist = dist[j];
				u = j;
			}
		}
		if (u == -1) break;

		visit[u] = true;
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u + 1][v] > 0 && !visit[v]) {
				if (dist[u] + adjMatrix[u + 1][v] < dist[v]) {
					dist[v] = dist[u] + adjMatrix[u + 1][v];
					pre[v] = u;
				}
			}
		}
	}
	vector<int> path;
	if (dist[end] == INT_MAX) return path;
	for (int v = end; v != -1; v = pre[v]) {
		path.insert(path.begin(), v);
	}
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix[0][0];
	vector<int> dist(n, INT_MAX);
	vector<int> pre(n, -1);

	dist[start] = 0;
	for (int i = 0; i < n - 1; i++) {
		bool update = false;
		for (int u = 0; u < n; u++) {
			if (dist[u] == INT_MAX) continue;
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u + 1][v] > 0) {
					if (dist[u] + adjMatrix[u + 1][v] < dist[v]) {
						dist[v] = dist[u] + adjMatrix[u + 1][v];
						pre[v] = u;
						update = true;
					}
				}
			}
		}
		if (!update) break;
	}
	for (int u = 0; u < n; u++) {
		if (dist[u] == INT_MAX) continue;
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u + 1][v] > 0) {
				if (dist[u] + adjMatrix[u + 1][v] < dist[v]) {
					return{};
				}
			}
		}
	}
	vector<int> path;
	if (dist[end] == INT_MAX) return path;
	for (int v = end; v != -1; v = pre[v]) {
		path.insert(path.begin(), v);
	}
	return path;
}

