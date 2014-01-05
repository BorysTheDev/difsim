#include "e_core.h"
#include "hankel.h"
#include "simple_math.h"
#include"chebyshev.h"

using namespace tps;
using namespace crv;

typedef ParametricCurvePoint pcp;
typedef DiscretizeCurve dc;

namespace epl {

/**
 * @brief gamma - Euler-Mascheroni constant
 */
const double gamma = 0.57721566490153286060651209008240243104215933593992;

/**
 * @brief core - difraction function for EPolarization wave
 * @param wn
 * @return
 */
complex core(const RPoint& tau, const RPoint& t, real wn)
{
  return mth::h2(wn * mth::dist(t, tau));
}

/**
 * @brief lim - limit in point
 * @param d - derivative in point
 * @param wn - wavenumber
 * @return
 */
complex lim(RPoint d, real wn) {
  using namespace std;
  typedef tps::complex cmpx;
  return 1.0 - cmpx(0, 2 / M_PI) * (log(wn * hypot(d.x, d.y) / 2) + gamma);
}

/**
 * @brief asymp - asymptotics for hankel function
 * @param t
 * @param tau
 * @return
 */
complex asymp(const real& t, const real& tau) {
  using namespace std;
  return -(tps::complex(0, 2 * log(abs(t - tau)) / M_PI));
}

/**
 * @brief Ln - integral for ln
 * @param t0
 * @param t_
 * @param n
 * @return
 */
tps::real Ln(const tps::real& t, const tps::real& tau, const int n) {
  using namespace std;
  tps::real sum = 0;
  for (int p = 1; p < n; p++) {
    sum += mth::tcheb(p, tau) * mth::tcheb(p, t) / p;
  }
  return -(log(2) + 2 * sum);
}

/**
 * @brief smoothCore - this is core - asymp
 * @param t
 * @param t1
 * @param wn
 * @return
 */
complex smoothCore(const pcp& tau, const pcp& t, real wn)
{
  return (tau.t == t.t) ? lim(tau.d, wn) :
                          core(tau, t, wn) - asymp(tau.t, t.t);
}


tps::complex mdoCore(const pcp& p1, const pcp& p2, bool sinhularity,
                     int size, tps::real wn)
{
  if (sinhularity){
    return (M_PI / size) * smoothCore(p1 ,p2, wn)
        - complex(0,2) * Ln(p1.t, p2.t, size);
  } else {
    return (M_PI / size) * core(p1 ,p2, wn);
  }
}
}
