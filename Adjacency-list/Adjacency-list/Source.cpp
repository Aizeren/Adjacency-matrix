#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int nodesNumber = 0;
	string str;
	ifstream nodes;
	
	nodes.open("../../Resources/Nodes.csv");
	if (!nodes.is_open())
		return 1;
	//count number of rows
	while (getline(nodes, str)) {
		nodesNumber++;
	}
	nodes.close();	

	//array of nodes
	int *nodesIndexes = new int[nodesNumber];

	nodes.open("../../Resources/Nodes.csv");
	for (int i = 0; i < nodesNumber; i++) {
		getline(nodes, str);
		nodesIndexes[i] = stoi(str);
	}
	nodes.close();

	ofstream adjList("../../Resources/Adjacency-list.csv");
	if (!adjList.is_open())
		return 3;
	ifstream adjMatrix("../../Resources/Adjacency-matrix.csv");
	if (!adjMatrix.is_open())
		return 4;
	//form adjacency list
	for (int i = 0; i < nodesNumber; i++) {
		adjList << nodesIndexes[i];
		for (int j = 0; j < nodesNumber - 1; j++) {
			getline(adjMatrix, str, ';');
			if (stoi(str) == 1)
				adjList << ';' << nodesIndexes[j];
		}
		getline(adjMatrix, str);
		if (stoi(str) == 1)
			adjList << ';' << nodesIndexes[nodesNumber-1];
		adjList << '\n';
	}
	adjList.close();
	adjMatrix.close();

	return 0;
}