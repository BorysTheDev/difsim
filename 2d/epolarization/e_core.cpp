#include "e_core.h"
#include "hankel.h"
#include "simple_math.h"

using namespace tps;
using namespace crv;

typedef ParametricCurvePoint pcp;

namespace epl {

//Euler-Mascheroni constant
const double gamma = 0.57721566490153286060651209008240243104215933593992;

complex core(const RPoint& tau, const RPoint& t, real wn)
{
  return mth::h2(wn * mth::dist(t, tau));
}

complex lim(RPoint d, real wn) {
  using namespace std;
  typedef tps::complex cmpx;
  return 1.0 - cmpx(0, 2 / M_PI) * (log(wn * hypot(d.x, d.y) / 2) + gamma);
}

/* asymptotic for Hankel function */
complex asymp(const real& t, const real& tau) {
  using namespace std;
  return -(tps::complex(0, 2 * log(abs(t - tau)) / M_PI));
}

complex smoothCore(const pcp& tau, const pcp& t, real wn)
{
  return core(tau, t, wn) - asymp(tau.t, t.t);
}

}
