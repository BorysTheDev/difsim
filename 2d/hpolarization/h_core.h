#ifndef CORE_H_
#define CORE_H_

#include "discretize_curve.h"

namespace hpl {

tps::complex core(const crv::ParametricCurvePoint&,
    const crv::ParametricCurvePoint&, tps::real wn);

tps::complex smoothCore(const crv::ParametricCurvePoint& t,
    const crv::ParametricCurvePoint& t1, tps::real wn);

}

#endif /* CORE_H_ */
