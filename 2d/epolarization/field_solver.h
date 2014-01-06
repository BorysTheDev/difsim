#ifndef FIELD_SOLVER_H_
#define FIELD_SOLVER_H_

#include "discretize_curve.h"
#include "types.h"
#include <vector>


class FieldSolver {
  typedef std::vector<crv::DiscretizeCurve> CurvesList;
  typedef std::vector<std::vector<tps::complex>> CurrentList;
public:
	FieldSolver(const CurvesList& curves, const CurrentList& currents,
      tps::real k) : curves(curves), currents(currents), waveNumber(k) {
	}
  tps::complex field(const tps::RPoint& p) const;

  tps::complex farField(const tps::real angle) const;
private:

	const CurvesList& curves;
	const CurrentList& currents;
  const tps::real waveNumber;
};




#endif /* FIELD_SOLVER_H_ */
