#ifndef MATRIXUTILS_H_
#define MATRIXUTILS_H_

#include <vector>
#include <stdlib.h>

typedef std::vector<double> column;
typedef std::vector<column> matrix;

matrix matrixMultiply(const matrix, const matrix);
double vectorMultiply(const column, const column);
column vectorMultiplyByScalar(const column, const double);
column vectorSubtraction(const column, const column);
double vectorNorm(const column v);
column vectorDivisionByScalar(const column, const double);

#endif /* MATRIXUTILS_H_ */
