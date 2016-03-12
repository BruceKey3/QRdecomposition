#include "MatrixUtils.h"

#include <assert.h>
#include <math.h>
#include <iostream>
#include <iterator>

using namespace std;

/* Print a matrix to stdout */
void printMatrix(matrix m) {
	for (int i = 0; i < m.size(); i++) {
		for (matrix::iterator it = m.begin(); it != m.end(); ++it) {
			column c = (*it);
			//round to 7 decimal points
			double precision = 10000000.0;
			double val = round(c[i] * precision) / precision;
			cout << "\t" << val << "\t";
		}
		cout << endl;
	}
}

/* Multiply m1 by m2 */
matrix matrixMultiply(const matrix m1, const matrix m2)
{
	assert(m1.size() == m2[0].size());
	matrix res(m1.size(), column(m2[0].size()));
	for(int row = 0; row < m2[0].size(); row++)
	{
		for(int col = 0; col < m1.size(); col++)
		{
			for(int inner = 0; inner < m1[0].size(); inner++)
			{
			    res[row][col] += m2[row][inner] * m1[inner][col];
			}
		}
	}
	return res;
}

/* (v1)T * v2 */
double vectorMultiply(const column v1,const column v2)
{
	assert(v1.size() == v2.size());
	double res = 0;
	for(int i = 0; i < v1.size(); i++)
	{
		res += v1[i]*v2[i];
	}
	return res;
}

/* x*V1 where x is a scalar */
column vectorMultiplyByScalar(const column v,const double scalar)
{
	column res = v;
	for(int i = 0; i < v.size(); i++)
	{
		res[i] = v[i]*scalar;
	}
	return res;
}

/* V1 - V2 */
column vectorSubtraction(const column v1,const column v2)
{
	assert(v1.size() == v2.size());
	column res = v1;
	for(int i = 0; i < v1.size(); i++)
	{
		res[i] = v1[i] - v2[i];
	}
	return res;
}

/* Euclidean norm of v */
double vectorNorm(const column v)
{
	double res = 0;
	for(int i = 0; i < v.size(); i++)
	{
		res += v[i]*v[i];
	}
	return sqrt(fabs(res));
}

/* v / x where x is a scalar */
column vectorDivisionByScalar(const column v, const double scalar)
{
	column res = v;
	for(int i = 0; i < v.size(); i++)
	{
		// Avoid division by 0
		if(scalar == 0)
		{
			res[i] = 0;
		}
		else
		{
			res[i] = double(v[i]) / double(scalar);
		}
	}
	return res;
}
