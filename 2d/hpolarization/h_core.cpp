#include "h_core.h"
#include "hankel.h"
#include "simple_math.h"

using namespace tps;
using namespace crv;

typedef ParametricCurvePoint pcp;

namespace hpl {

complex core(const pcp& tau, const pcp& t, real wn)
{
  real difx = t.x - tau.x;
  real dify = t.y - tau.y;
  real z2 = difx * difx + dify * dify;
  real z = std::sqrt(z2);
  real zdzdt = difx * t.d.x + dify * t.d.y;
  real zdzdtau = -difx * tau.d.x - dify * tau.d.y;
  //real dzdt   = zdzdt / z;
  //real dzdtau = zdzdtau / z;
  real dzdtdtau = ((-t.d.x * tau.d.x - t.d.y * tau.d.y) * z - zdzdt * zdzdtau) / z2;
  complex h2_1 = mth::h2(1, z);
  return wn * ((mth::h2(2, z) - h2_1 / z) * (zdzdt * zdzdtau) / z - h2_1 * dzdtdtau);
}

complex smoothCore(const pcp& tau, const pcp& t, real wn)
{
  real p       = std::hypot(t.d.x, t.d.y);
  real dp      = 2 * (t.d.x * t.d2.x + t.d.y * t.d2.y);
  real tmtau   = std::abs(t.t - tau.t);
  real lntmtau = std::log(tmtau);
  complex sm1(0, 2.0 / M_PI / mth::sqr(tmtau));
  complex sm2(0, (2.0 / M_PI) * 2 * wn * p * lntmtau);
  complex sm3(0, (2.0 / M_PI) * 2 * wn * tmtau * dp * lntmtau);
  return core(t, tau, wn) - sm1 - (sm2 + sm3) / complex(4, 0);
}

}
