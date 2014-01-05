#ifndef E_CORE_
#define E_CORE_

#include "discretize_curve.h"

namespace epl {

/**
 * @brief mdoCore
 * @param p1 - first curve point
 * @param p2 - second curve point
 * @param sinhularity - it's true if curve1 == curve2
 * @param size - second curve points number
 * @param wn - wavenumber
 * @return
 */
tps::complex mdoCore(const crv::ParametricCurvePoint& p1,
                     const crv::ParametricCurvePoint& p2,
                     bool sinhularity, int size, tps::real wn);

}

#endif /* E_CORE_ */
