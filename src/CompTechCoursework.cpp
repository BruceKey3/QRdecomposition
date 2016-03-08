#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "MatrixUtils.h"

using namespace std;

#define MAX 10
#define MIN 0
#define DIMENSION 3

static int dimension = DIMENSION;

matrix readFromFile(char *fileName) {
	ifstream inputFile(fileName);
	string line;
	if (inputFile.is_open()) {
		vector<float> temp;
		while(getline(inputFile, line))
		{

			istringstream iss(line);
			float sub;
			while(iss >> sub)
			{
			  temp.push_back(sub);
			}
		}
		dimension = sqrt(temp.size());
		matrix res(dimension, column(dimension));
		for(int i = 0; i < dimension; i++)
		{
			for(int j = 0; j < dimension; j++)
			{
				res[i][j] = temp[j*dimension + i];
			}
		}
		return res;
	}
	exit(-1);


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

#define LIMIT (0.00000001)

bool isNearlyDiagonal(matrix a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (fabs(a[i][j]) >= LIMIT && fabs(a[j][i]) >= LIMIT) {
				return false;
			}
		}
	}
	return true;
}

matrix qrIteration(matrix a, vector<matrix> &qk) {
	while (!isNearlyDiagonal(a)) {
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
		res = matrixMultiply(res, qk[i]);
	}
	return res;
}

int main(int argc, char** argv) {
	srand(time(NULL));
	matrix m(dimension, column(dimension));

	if (argc > 1) {
		m = readFromFile(argv[1]);
	} else {
		m = getRandomSymmetric(m.size());
	}
	printMatrix(m);
	matrix q(m.size(), column(m.size()));
	matrix r(m.size(), column(m.size()));
	decompose(m, q, r);
	cout << endl;
	printMatrix(q);
	cout << endl;
	printMatrix(r);
	/*
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
	outputFile << "NOTE: Read each column as an eigenvector." << endl;
	matrix eigenVectors = getEigenVectors(qk);
	for (int i = 0; i < dimension; i++) {
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
	outputFile.close();
	*/
	return 0;
}

