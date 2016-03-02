#include "MatrixUtils.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>

using namespace std;

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

column vectorMultiplyByScalar(const column v,const double scalar)
{
	column res = v;
	for(int i = 0; i < v.size(); i++)
	{
		res[i] = v[i]*scalar;
	}
	return res;
}

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

double vectorNorm(const column v)
{
	double res = 0;
	for(int i = 0; i < v.size(); i++)
	{
		res += v[i]*v[i];
	}
	return sqrt(res);
}

column vectorDivisionByScalar(const column v, const double scalar)
{
	column res = v;
	for(int i = 0; i < v.size(); i++)
	{
		res[i] = double(v[i]) / double(scalar);
	}
	return res;
}
