#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
int ** multiplication(int ** a, int ** b, int n);
int ** logSum(int ** a, int ** b, int n);
int ** transp(int ** a, int n);
int ** logMult(int ** a, int ** b, int n);
int min(int a, int b);
int diameter(int * ecc, int n);
int radius(int * ecc, int n);
float avgPathLength(int ** arr, int n);
int * centralVertex(int *ecc, int radius, int n);
int * periphVertex(int *ecc, int diameter, int n);
float averageVertexPower(int ** arr, int n);
int ** CommonNeighbors(int ** adjMatrix, int n);
float ** JaccardCoefficient(int ** adjMatrix, int n);
float ** Adamic(int ** adjMatrix, int n);
int ** PreferentialAttachment(int ** adjMatrix, int n);