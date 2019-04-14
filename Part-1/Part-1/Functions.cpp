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