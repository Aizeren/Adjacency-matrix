#include "Header.h"

using namespace std;

int main() {
	int nodesNumber = 0, componentsNumber = 0;
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
	ifstream adjMatrix("../../Resources/Adjacency-matrix.csv");
	if (!adjMatrix.is_open())
		return 4;

	//initialize arrays
	int ** currMatrix = new int *[nodesNumber];
	int ** resMatrix = new int *[nodesNumber];
	int * numberOfNodesInComponents = new int[nodesNumber];
	int * nodesArr = new int[nodesNumber];
	for (int i = 0; i < nodesNumber; i++) {
		numberOfNodesInComponents[i] = 0;
		nodesArr[i] = 1;
		currMatrix[i] = new int[nodesNumber];
		resMatrix[i] = new int[nodesNumber];
	}
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber-1; j++) {
			getline(adjMatrix, str, ',');
			currMatrix[i][j] = stoi(str);
			resMatrix[i][j] = 0;
		}
		getline(adjMatrix, str);
		currMatrix[i][nodesNumber-1] = stoi(str);
		resMatrix[i][nodesNumber-1] = 0;
	}
	
	//находим матрицу достижимости
	for (int i = 0; i < nodesNumber; i++) {
		currMatrix = multiplication(currMatrix, currMatrix, nodesNumber);
		resMatrix = logSum(resMatrix, currMatrix, nodesNumber);
	}
	//находим матрицу связности
	resMatrix = logMult(resMatrix, transp(resMatrix, nodesNumber) , nodesNumber);
	for (int i = 0; i < nodesNumber; i++) {
		resMatrix[i][i] = 1;
	}

	//находим компоненты связности
	int counter = nodesNumber;
	int currFirstRow = 0;
	while (counter > 0) {
		for (int i = 0; i < nodesNumber; i++) {
			if (nodesArr[i] == 1)
			{
				currFirstRow = i;
				break;
			}
		}
		for (int i = 0; i < nodesNumber; i++) {
			if (resMatrix[currFirstRow][i] == 1) {
				nodesArr[i] = 0;
				counter--;
				numberOfNodesInComponents[componentsNumber]++;
			}
		}
		componentsNumber++;
	}

	int maxComponentNumber = 0;
	for (int i = 0; i < nodesNumber; i++) {
		if (numberOfNodesInComponents[i] > maxComponentNumber)
			maxComponentNumber = numberOfNodesInComponents[i];
	}

	cout << (float)maxComponentNumber / (float)nodesNumber << endl;

	system("pause");
	return 0;
}