#include "Header.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int nodesNumber = 0, componentsNumber = 0, arrRadius, arrDiameter;
	float avgPathLngth;
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
	ifstream adjMatrixStream("../../Resources/Adjacency-matrix.csv");
	if (!adjMatrixStream.is_open())
		return 4;

	//initialize arrays
	int ** adjMatrix = new int *[nodesNumber];
	int ** currMatrix = new int *[nodesNumber];
	int ** resMatrix = new int *[nodesNumber];
	int * numberOfNodesInComponents = new int[nodesNumber];
	int * nodesArr = new int[nodesNumber];//вспомогательная матрица
	for (int i = 0; i < nodesNumber; i++) {
		numberOfNodesInComponents[i] = 0;
		nodesArr[i] = 1;
		currMatrix[i] = new int[nodesNumber];
		resMatrix[i] = new int[nodesNumber];
		adjMatrix[i] = new int[nodesNumber];
	}
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber-1; j++) {
			getline(adjMatrixStream, str, ',');
			adjMatrix[i][j] = stoi(str);
			resMatrix[i][j] = 0;
			currMatrix[i][j] = adjMatrix[i][j];
		}
		getline(adjMatrixStream, str);
		adjMatrix[i][nodesNumber-1] = stoi(str);
		resMatrix[i][nodesNumber-1] = 0;
		currMatrix[i][nodesNumber - 1] = adjMatrix[i][nodesNumber - 1];
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
			if ((resMatrix[currFirstRow][i] == 1) && (nodesArr[i] == 1)) {
				nodesArr[i] = 0;
				counter--;
				numberOfNodesInComponents[componentsNumber]++;
			}
		}
		componentsNumber++;
	}

	int maxComponentAmount = 0;
	for (int i = 0; i < nodesNumber; i++) {
		if (numberOfNodesInComponents[i] > maxComponentAmount)
			maxComponentAmount = numberOfNodesInComponents[i];
	}

	cout << "Доля узлов, пренадлежащих к наибольшей компоненте слабой связности: " << (float)maxComponentAmount / (float)nodesNumber << endl;

	//граф - наибольшая компонента связности
	currFirstRow = 0;
	int ** maxComponentAdjMatrix = new int *[maxComponentAmount];
	int * nodesInGraph = new int[nodesNumber];
	for (int i = 0; i < maxComponentAmount; i++) {
		maxComponentAdjMatrix[i] = new int[maxComponentAmount];
	}
	for (int i = 0; i < maxComponentAmount; i++) {
		for (int j = 0; j < maxComponentAmount; j++) {
			maxComponentAdjMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < nodesNumber; i++) {
		nodesArr[i] = 1;
	}
	//находим какие узлы содержатся в наибольшей компоненте связности(nodesInGraph)
	while (counter < maxComponentAmount-1) {
		counter = 0;
		for (int i = 0; i < nodesNumber; i++) {
			nodesInGraph[i] = 0;
		}
		for (int i = 0; i < nodesNumber; i++) {
			if (nodesArr[i] == 1)
			{
				currFirstRow = i;
				break;
			}
		}
		for (int i = 0; i < nodesNumber; i++) {
			if ((resMatrix[currFirstRow][i] == 1) && (nodesArr[i] == 1)) {
				nodesArr[i] = 0;
				nodesInGraph[i] = 1;
				counter++;
			}
		}
	}
	
	//строим матрицу смежности графа(наибольшей компоненты связности)
	int counteri = 0;
	int counterj = 0;
	for (int i = 0; i < nodesNumber; i++) {
		if (nodesInGraph[i] == 1) {
			for (int j = 0; j < nodesNumber; j++) {
				if (nodesInGraph[j] == 1) {
					maxComponentAdjMatrix[counteri][counterj] = adjMatrix[i][j];
					counterj++;
				}
			}
			counteri++;
			counterj = 0;
		}
	}

	//с помощью алгоритма Флойда - Уоршелла найдем матрицу расстояний для графа
	int ** pathLengthArr = new int *[maxComponentAmount];
	for (int i = 0; i < maxComponentAmount; i++) {
		pathLengthArr[i] = new int[maxComponentAmount];
	}
	for (int i = 0; i < maxComponentAmount; i++) {
		for (int j = 0; j < maxComponentAmount; j++) {
			if (maxComponentAdjMatrix[i][j] == 1)
				pathLengthArr[i][j] = 1;
			else
				pathLengthArr[i][j] = maxComponentAmount; //(вместо беск-ти)
							//длина пути между двумя вершинами не может превышаь кол-во вершин в графе
		}
	}

	for (int k = 0; k < maxComponentAmount; k++)
		for (int i = 0; i < maxComponentAmount; i++)
			for (int j = 0; j < maxComponentAmount; j++)
				pathLengthArr[i][j] = min(pathLengthArr[i][j], pathLengthArr[i][k] + pathLengthArr[k][j]);

	int *ecc = new int[maxComponentAmount]; //эксцентриситет

	for (int i = 0; i < maxComponentAmount; i++) {
		for (int j = 0; j < maxComponentAmount; j++) {
			if (pathLengthArr[i][j] > ecc[i])
				ecc[i] = pathLengthArr[i][j];
		}
	}

	int * centralVnumbers = new int[maxComponentAmount];
	int * periphVnumbers = new int[maxComponentAmount];
	for (int i = 0; i < maxComponentAmount; i++) {
		centralVnumbers[i] = 0;
		periphVnumbers[i] = 0;
	}
	arrRadius = radius(ecc, maxComponentAmount); //радиус графа
	arrDiameter = diameter(ecc, maxComponentAmount); //диаметр графа
	centralVnumbers = centralVertex(ecc, arrRadius, maxComponentAmount); //если в i-й ячейке стоит 1, то вершина - вентральная
	periphVnumbers = periphVertex(ecc, arrDiameter, maxComponentAmount); //аналогично с центральными
	avgPathLngth = avgPathLength(pathLengthArr, maxComponentAmount); //средняя длина пут в графе
	cout << "Радиус графа: " << arrRadius << endl;
	cout << "Диаметр графа: " << arrDiameter << endl;
	cout << "Средняя длина пути графа: " << avgPathLngth << endl;
	cout << "Центральные вершины графа: " << endl;
		nodes.open("../../Resources/Nodes.csv");
		if (!nodes.is_open())
			return 1;
		for (int i = 0; i < nodesNumber; i++) {
			getline(nodes, str);
			nodesArr[i] = stoi(str);
		}
		nodes.close();
		ofstream nodesInGraphStream("../../Resources/Nodes-of-max-connected-component.csv");
		for (int i = 0; i < nodesNumber; i++) {
			if (nodesInGraph[i] == 1)
				nodesInGraphStream << nodesArr[i] << endl;
		}
		nodesInGraphStream.close();
		ofstream adjMatrixOfGraph("../../Resources/Adjacency-matrix-for-max-connected-component.csv");
		for (int i = 0; i < maxComponentAmount; i++) {
			for (int j = 0; j < maxComponentAmount-1; j++) {
				adjMatrixOfGraph << maxComponentAdjMatrix[i][j] << ",";
			}
			adjMatrixOfGraph << maxComponentAdjMatrix[i][maxComponentAmount - 1] << endl;
		}
		adjMatrixOfGraph.close();
	counter = 0;
	for (int i = 0; i < nodesNumber; i++) {
		if (nodesInGraph[i] == 1) {
			if (centralVnumbers[counter] == 1) {
				cout << "id" << nodesArr[i] << endl;
			}
			counter++;
		}
	}
	cout << "Периферийные вершины графа: " << endl;
	counter = 0;
	for (int i = 0; i < nodesNumber; i++) {
		if (nodesInGraph[i] == 1) {
			if (periphVnumbers[counter] == 1) {
				cout << "id" << nodesArr[i] << endl;
			}
			counter++;
		}
	}

	float avgVertexPower;
	avgVertexPower = averageVertexPower(maxComponentAdjMatrix, maxComponentAmount);
	cout << "Средняя степень вершины в графе: " << avgVertexPower << endl;
	/*for (int j = 0; j < maxComponentAmount; j++) {
		cout << avgVertexPower[j] << " ";
	}*/
	/*cout << endl;
	for (int j = 0; j < maxComponentAmount; j++) {
		cout << centralVnumbers[j] << " ";
	}*/

	/*for (int i = 0; i < maxComponentAmount; i++) {
		for (int j = 0; j < maxComponentAmount; j++) {
			cout << pathLengthArr[i][j] << " ";
		}
		cout << endl;
	}*/

	system("pause");
	return 0;
}