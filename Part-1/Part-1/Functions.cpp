#include "Header.h"
int ** multiplication(int ** a, int ** b, int n) {
	int ** res = a;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = 0;
			for (int k = 0; k < n; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
			if (res[i][j] != 0)
				res[i][j] = 1;
		}
	}
	return res;
}
int ** logSum(int ** a, int ** b, int n) {
	int ** res = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((a[i][j] == 1) || (b[i][j] == 1))
				res[i][j] = 1;
			else
				res[i][j] = 0;
		}
	}
	return res;
}
int ** transp(int ** a, int n) {
	int ** res = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = a[j][i];
		}
	}
	return res;
}

int ** logMult(int ** a, int ** b, int n) {
	int ** res = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((a[i][j] == 1) && (b[i][j] == 1))
				res[i][j] = 1;
			else
				res[i][j] = 0;
		}
	}
	return res;
}

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int diameter(int * ecc, int n) {
	int res = 0;
	for (int j = 0; j < n; j++)
		if (ecc[j] > res)
			res = ecc[j];
	return res;
}
int radius(int * ecc, int n) {
	int res = n;
	for (int i = 0; i < n; i++)
		if (res > ecc[i])
			res = ecc[i];
	return res;
}
float avgPathLength(int ** arr, int n) {
	float res = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res += arr[i][j];
	return res/(n*n);
}
int * centralVertex(int *ecc, int radius, int n) {
	int * res = new int[n];
	for (int i = 0; i < n; i++) {
		if (ecc[i] == radius)
			res[i] = 1;
		else
			res[i] = 0;
	}
	return res;
}
int * periphVertex(int *ecc, int diameter, int n) {
	int * res = new int[n];
	for (int i = 0; i < n; i++) {
		if (ecc[i] == diameter)
			res[i] = 1;
		else
			res[i] = 0;
	}
	return res;
}
float averageVertexPower(int ** arr, int n) {
	float res = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res += arr[i][j];

	return res/n;
}