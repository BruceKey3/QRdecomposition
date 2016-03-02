#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "MatrixUtils.h"

using namespace std;



#define MAX 10
#define MIN 0
#define DIMENSION 3

void printMatrix(matrix m) {
	int row = 0;
	for (int i = 0; i < DIMENSION; i++)
	{
		for (matrix::iterator it = m.begin(); it != m.end(); ++it) {
			column c = (*it);
			cout << "   " << c[i] << "   ";
		}
		cout << endl;
	}
}

/* Get a random float between min and max */
double getRandomNumber(double min, double max) {
return (rand() % (int) ((max * 10) + 1)) / max;
}

/* Get a symmetric matric populated by random floats */
matrix getRandomSymmetric(void) {
  matrix sym(DIMENSION, column(DIMENSION));

  column *c = &*sym.begin();
  for(int i = 0; i < DIMENSION; i++)
  {
	  float ran = getRandomNumber(MIN,MAX);
	  c[i][i] = ran;
	  for(int j = i+1; j < DIMENSION; j++)
	  {
		  ran = getRandomNumber(MIN,MAX);
		  c[i][j] = ran;
		  c[j][i] = ran;
	  }
  }
  return sym;
}

/* decompose u and store result in q and r */
void decompose(matrix u, matrix &q, matrix &r)
{
	for (int i = 0; i < DIMENSION; i++)
	{
		q[i] = u[i];
		for (int j = 0; j < i; j++)
		{
			// r[i,j] = q[i]T u[i]
			r[j][i] = vectorMultiply(q[j], u[i]);
			//q[i] = q[i] - r[j,i]*q[j]
			q[i] = vectorSubtraction(q[i], vectorMultiplyByScalar(q[j], r[j][i]));
		}
		//r[i][i] = ||q[i]||;
		r[i][i] = vectorNorm(q[i]);
		//q[i] = q[i] / r[i,i];
		q[i] = vectorDivision(q[i], r[i][i]);
	}
}

int main() {
srand(time(NULL));
matrix m(DIMENSION, column(DIMENSION));
m = getRandomSymmetric();
m[0][0] = 1;
m[0][1] = 0;
m[0][2] = 1;

m[1][0] = 1;
m[1][1] = 0;
m[1][2] = 0;

m[2][0] = 2;
m[2][1] = 1;
m[2][2] = 0;
matrix q(DIMENSION, column(DIMENSION));
matrix r(DIMENSION, column(DIMENSION));
decompose(m,q,r);
printMatrix(m);
cout << "---------" << endl;
printMatrix(q);
cout << "---------" << endl;
printMatrix(r);
return 0;
}

