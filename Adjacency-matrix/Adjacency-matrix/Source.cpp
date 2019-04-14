#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int nodesNumber = 0, targetIndex, sourceIndex;
	string str, target, source;
	ifstream nodes;

	nodes.open("../../Resources/Nodes.csv");
	if (!nodes.is_open())
		return 1;
	//count number of rows
	while (getline(nodes, str)) {
		nodesNumber++;
	}
	nodes.close();
	//initialize adj-matrix
	int ** arr = new int *[nodesNumber];
	for (int i = 0; i < nodesNumber; i++) {
		arr[i] = new int[nodesNumber];
	}
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber; j++) {
			arr[i][j] = 0;
		}
	}
	
	//array of nodes
	int *nodesIndexes = new int[nodesNumber];

	nodes.open("../../Resources/Nodes.csv");
	for (int i = 0; i < nodesNumber; i++) {
		getline(nodes, str);
		nodesIndexes[i] = stoi(str);
	}
	nodes.close();

	ifstream edges;
	edges.open("../../Resources/Edges.csv");
	if (!edges.is_open())
		return 2;
	//read source and target from edges list, search for appropriate cell in adjacency matrix, write 1 when found
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

	//form adjacency matrix
	ofstream adjMatrix("../../Resources/Adjacency-matrix.csv");
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