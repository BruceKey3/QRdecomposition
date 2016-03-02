#include "MatrixUtils.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
using namespace std;

double vectorMultiply(const column v1,const column v2)
{
	assert(v1.size() == v2.size());
	float res = 0;
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

column vectorDivision(const column v, const double scalar)
{
	column res = v;
	for(int i = 0; i < v.size(); i++)
	{
		res[i] = v[i] / scalar;
	}
	return res;
}
