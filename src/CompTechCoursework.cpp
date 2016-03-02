#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "MatrixUtils.h"
#include <limits>
#include <cmath>
#include <fstream>

using namespace std;

#define MAX 10
#define MIN 0
#define DIMENSION 3

void printMatrix(matrix m) {
	for (int i = 0; i < m.size(); i++) {
		for (matrix::iterator it = m.begin(); it != m.end(); ++it) {
			column c = (*it);
			//round to 7 decimal points
			double precision = 10000000.0;
			double val = round(c[i] * precision) / precision;
			cout << "       " << val << "       ";
		}
		cout << endl;
	}
}

/* Get a random float between min and max */
double getRandomNumber(double min, double max) {
	return (rand() % (int) ((max * 10) + 1)) / max;
}

/* Get a symmetric matric populated by random floats */
matrix getRandomSymmetric(int size) {
	matrix sym(size, column(size));

	column *c = &*sym.begin();
	for (int i = 0; i < size; i++) {
		float ran = getRandomNumber(MIN, MAX);
		c[i][i] = ran;
		for (int j = i + 1; j < size; j++) {
			ran = getRandomNumber(MIN, MAX);
			c[i][j] = ran;
			c[j][i] = ran;
		}
	}
	return sym;
}

/* decompose u and store result in q and r */
void decompose(matrix u, matrix &q, matrix &r) {
	for (int i = 0; i < u.size(); i++) {
		q[i] = u[i];
		for (int j = 0; j < i; j++) {
			// r[j,i] = q[j]T u[i]
			r[i][j] = vectorMultiply(q[j], u[i]);
			//q[i] = q[i] - r[j,i]*q[j]
			q[i] = vectorSubtraction(q[i],
					vectorMultiplyByScalar(q[j], r[i][j]));
		}
		//r[i][i] = ||q[i]||;
		r[i][i] = vectorNorm(q[i]);
		//q[i] = q[i] / r[i,i];
		q[i] = vectorDivisionByScalar(q[i], r[i][i]);
	}
}
#define LIMIT (0.0000000000000000000000000001)
matrix qrIteration(matrix a, vector<matrix> &qk) {
	while (fabs(a[0][DIMENSION - 1]) >= LIMIT
			&& fabs(a[DIMENSION - 1][0]) >= LIMIT) {
		matrix q(a.size(), column(a.size()));
		matrix r(a.size(), column(a.size()));
		decompose(a, q, r);
		qk.push_back(q);
		a = matrixMultiply(r, q);
	}
	return a;
}

vector<float> getEigenValues(matrix m) {
	vector<float> res;
	for (int i = 0; i < m.size(); i++) {
		res.push_back(m[i][i]);
	}
	return res;
}

matrix getEigenVectors(vector<matrix> qk) {
	matrix res = qk[0];
	for (int i = 1; i < qk.size(); i++) {
		res = matrixMultiply(qk[i], res);
	}
	return res;
}

int main() {
	srand(time(NULL));
	matrix m(DIMENSION, column(DIMENSION));

	m = getRandomSymmetric(DIMENSION);

	m[0][0] = 1;
	m[0][1] = 1;
	m[0][2] = 1;

	m[1][0] = 1;
	m[1][1] = 1;
	m[1][2] = 1;

	m[2][0] = 1;
	m[2][1] = 1;
	m[2][2] = 1;

	vector<matrix> qk;
	matrix eigenValuesMatrix = qrIteration(m, qk);

	ofstream outputFile;
	outputFile.open("results.txt");

	outputFile << "eigenValues: ";
	vector<float> eigenValues = getEigenValues(eigenValuesMatrix);
	for (int i = 0; i < eigenValues.size(); i++) {
		outputFile << eigenValues[i] << " ";
	}
	outputFile << endl;

	outputFile << "eigenVectors: " << endl;
	matrix eigenVectors = getEigenVectors(qk);

	for (int i = 0; i < DIMENSION; i++) {
		for (matrix::iterator it = eigenVectors.begin();
				it != eigenVectors.end(); ++it) {
			column c = (*it);
			//round to 7 decimal points
			double precision = 10000000.0;
			double val = round(c[i] * precision) / precision;
			outputFile << val << " ";
		}
		outputFile << endl;
	}

	return 0;
}

