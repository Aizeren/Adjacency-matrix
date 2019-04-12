#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int nodesNumber = 0, targetIndex, sourceIndex, i;
	string str, target, source;
	ifstream nodes;

	nodes.open("Resources/Nodes.csv");
	if (!nodes.is_open())
		return 1;
	//считаем кол-во строк
	while (getline(nodes, str)) {
		nodesNumber++;
	}
	nodes.close();
	//создаем матрицу смежности
	int ** arr = new int *[nodesNumber];
	for (int i = 0; i < nodesNumber; i++) {
		arr[i] = new int[nodesNumber];
	}
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber; j++) {
			arr[i][j] = 0;
		}
	}
	
	//массив для соот-ия id и индекса
	int *nodesIndexes = new int[nodesNumber];

	i = 0;
	nodes.open("Resources/Nodes.csv");
	while (getline(nodes, str)) {
		nodesIndexes[i] = stoi(str);
		i++;
	}
	nodes.close();

	ifstream edges;
	edges.open("Resources/Edges.csv");
	if (!edges.is_open())
		return 2;
	//считывам source и target из списка ребер, ищем соот-ую ячейку в матрице смежности, проставляем с соот-ую ячейку 1
	while (getline(edges, source, ',')) {
		getline(edges, target, '\n');
		for (int i = 0; i < nodesNumber; i++) {
			if (nodesIndexes[i] == stoi(source))
				sourceIndex = i;
			if (nodesIndexes[i] == stoi(target))
				targetIndex = i;
		}
		arr[sourceIndex][targetIndex] = 1;
	}
	edges.close();

	ofstream adjMatrix("Resources/Adjacency-matrix.csv");
	if (!adjMatrix.is_open())
		return 3;
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber-1; j++) {
			adjMatrix << arr[i][j] << ",";
		}
		adjMatrix << arr[i][nodesNumber-1] << endl;
	}
	adjMatrix.close();

	return 0;
}