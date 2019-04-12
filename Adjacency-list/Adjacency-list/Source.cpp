#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int nodesNumber = 0;
	string str;
	int i;
	ifstream nodes;
	
	nodes.open("Resources/Nodes.csv");
	if (!nodes.is_open())
		return 1;
	//считаем кол-во строк
	while (getline(nodes, str)) {
		nodesNumber++;
	}
	nodes.close();	

	//массив для соот-ия id и индекса
	int *nodesIndexes = new int[nodesNumber];

	i = 0;
	nodes.open("Resources/Nodes.csv");
	while (getline(nodes, str)) {
		nodesIndexes[i] = stoi(str);
		i++;
	}
	nodes.close();

	ofstream adjList("Resources/Adjacency-list.csv");
	if (!adjList.is_open())
		return 3;
	ifstream adjMatrix("Resources/Adjacency-matrix.csv");
	if (!adjMatrix.is_open())
		return 4;
	for (int i = 0; i < nodesNumber; i++) {
		adjList << nodesIndexes[i];
		for (int j = 0; j < nodesNumber - 1; j++) {
			getline(adjMatrix, str, ',');
			if (stoi(str) == 1)
				adjList << ',' << nodesIndexes[j];
		}
		getline(adjMatrix, str);
		if (stoi(str) == 1)
			adjList << ',' << nodesIndexes[nodesNumber-1];
		adjList << '\n';
	}
	adjList.close();
	adjMatrix.close();

	return 0;
}