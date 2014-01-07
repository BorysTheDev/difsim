#ifndef TYPES_H_
#define TYPES_H_
#include <complex>
#include "point.h"
#include "matrix.h"
#include <memory>
#include "inttypes.h"

namespace tps {

typedef uint_fast32_t fint;
typedef double real;
typedef std::complex<double> complex;
typedef mth::Point<real> RPoint;

typedef mtrx::Matrix<complex> CMatrix;
typedef std::unique_ptr<mtrx::Matrix<complex>> CMatrixUPtr;
}

#endif /* TYPES_H_ */
