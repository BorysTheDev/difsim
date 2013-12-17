#ifndef CORE_H_
#define CORE_H_

#include "discretize_curve.h"

namespace epl {

/*
 * wn - wave number
 */
tps::complex core(const tps::RPoint&,const tps::RPoint&, tps::real wn);

tps::complex smoothCore(const crv::ParametricCurvePoint& t,
    const crv::ParametricCurvePoint& t1, tps::real wn);

/* limit
 * wn - wave number
 * d - derivative
 */
tps::complex lim(tps::RPoint d, tps::real wn);
}

#endif /* CORE_H_ */
