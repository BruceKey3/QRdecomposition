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

/* Min and max values for random number
 generation when filling a matrix */
#define MAX 10
#define MIN 0

/* Default dimension of matrix */
#define DIMENSION 3

/* Defines limit which values should be under
 in order to be called diagonal */
#define LIMIT (0.00000001)

/* Global variable to store the dimension */
static int dimension = DIMENSION;

/* Read a matrix from a file.
 Must be numeric values separated by a space. */
matrix readFromFile(char *fileName) {
	ifstream inputFile(fileName);
	string line;

	// Check if the file opened successfully
	if (inputFile.is_open()) {
		vector<float> temp;
		// Read in the file
		while (getline(inputFile, line)) {

			istringstream iss(line);
			float sub;
			// Add each value into temporary storage
			while (iss >> sub) {
				temp.push_back(sub);
			}
		}
		// Assume square matrix, set dimension
		dimension = sqrt(temp.size());
		// Create the matrix and populate it
		matrix res(dimension, column(dimension));
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				res[i][j] = temp[j * dimension + i];
			}
		}

		return res;
	}
	// Exit if the file didn't open correctly
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

/* QR decomposition of u, stores result in q and r */
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

/* Check if the matrix is diagonal within acceptable bounds */
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

/* Use QR iteration to get the eigenvalues,
   stores intermediate q values so we can optionally
   calculate the eigenvectors later. */
matrix qrIteration(matrix a, vector<matrix> &qk) {
	// While matrix is not acceptably diagonal
	while (!isNearlyDiagonal(a)) {
		matrix q(a.size(), column(a.size()));
		matrix r(a.size(), column(a.size()));
		// Decompose a
		decompose(a, q, r);
		qk.push_back(q);
		// Next iteration
		a = matrixMultiply(r, q);
	}
	return a;
}

/* Get eigenvalues by reading down diagonal */
vector<float> getEigenValues(matrix m) {
	vector<float> res;
	for (int i = 0; i < m.size(); i++) {
		res.push_back(m[i][i]);
	}
	return res;
}

/* Use repeated multiplication to get eigenvectors
   from the list of intermediate q matrices */
matrix getEigenVectors(vector<matrix> qk) {
	matrix res = qk[0];
	for (int i = 1; i < qk.size(); i++) {
		res = matrixMultiply(res, qk[i]);
	}
	return res;
}

int main(int argc, char** argv) {
	// Initialse random seed
	srand(time(NULL));

	// Create empty matrix
	matrix m(dimension, column(dimension));

	// If the user passed in a file name
	if (argc > 1) {
		// Read from the file
		m = readFromFile(argv[1]);
	} else {
		// Else get a random matrix
		m = getRandomSymmetric(m.size());
		// Print the matrix (Optional)
		printMatrix(m);
	}

	// Initialise q and r and qk
	matrix q(m.size(), column(m.size()));
	matrix r(m.size(), column(m.size()));
	vector<matrix> qk;

	// Get matrix of eigenvalues
	matrix eigenValuesMatrix = qrIteration(m, qk);

	// Open results file
	ofstream outputFile;
	outputFile.open("results.txt");

	// Write eigenvalues to the file
	outputFile << "eigenValues: ";
	vector<float> eigenValues = getEigenValues(eigenValuesMatrix);
	for (int i = 0; i < eigenValues.size(); i++) {
		outputFile << eigenValues[i] << " ";
	}
	outputFile << endl;

	// Write the eigenvectors to the file
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
	// Close the file
	outputFile.close();

	return 0;
}

